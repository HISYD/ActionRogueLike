// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "DrawDebugHelpers.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EngineUtils.h"

ASGameModeBase::ASGameModeBase()
{
	SpawnTimeInterval = 2.0f;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASGameModeBase::SpawnTimeEplased, SpawnTimeInterval, true);
	
}

void ASGameModeBase::SpawnTimeEplased()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(GetWorld(), SpawnBotQuery, this, EEnvQueryRunMode::Type::RandomBest5Pct, nullptr);

	if (ensure(SpawnBotQuery))//保护避免因为没有从editor传入query时报错
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::DoOnQeuryFinish);    //因为上述可能异步执行，因此不能直接顺序执行，而应该绑定到时间上
	}
}

void ASGameModeBase::DoOnQeuryFinish(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Type::Success)
	{
		return;	
	}

	//每次试图创建的时候执行，遍历检查；目前的Enemy数量
	int32 NrOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)//一种好用的迭代器，返回所有继承自该基类的子类的实例
	{
		ASAICharacter* Bot = *It;
		USAttributeComponent* AttribComp = Cast<USAttributeComponent>(Bot->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttribComp && AttribComp->IsAlive())
		{
			NrOfAliveBots ++;
		}
	}

	
	
	MaxBotCount = 10.0f;
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	if (NrOfAliveBots >= MaxBotCount)
	{
		return;
	}
	
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.IsValidIndex(0))
	{
		FActorSpawnParameters SpawnParameters;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnClass, Locations[0], FRotator::ZeroRotator);
	}
}


