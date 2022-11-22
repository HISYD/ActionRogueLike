// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "DrawDebugHelpers.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EngineUtils.h"
#include "SCharacter.h"


//Console Variable 示例
static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable spawning of bots via timer"), ECVF_Cheat);
static TAutoConsoleVariable<bool> CVarDrawDebug(TEXT("su.bDrawDebug"), true, TEXT(""), ECVF_Cheat);
//su.可以帮助我们之后使用的时候快速定位所有su.开头的，类似于category


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
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		return;
	}
	
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

void ASGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();//之前Pawn死亡时disable了Controller的所有权。如果重启Player则INPUT无效。需要先清楚Controller的控制
		
		RestartPlayer(Controller);//要注意的是如果创建了些ui什么的试图从pawn里面读参数，那么新pawn的ui就会不动了捏
	}
}

void ASGameModeBase::DoOnActorKilled(AActor* VictimActor)
{
	ASCharacter* Player = Cast<ASCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;//使用局部的，而非全局的属性，因此下次handle自动被刷新了
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());//竟然tmd是用字符串名字绑定的吗//最后的是传入的参数
		
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, 2.0f, false);
	}
}


