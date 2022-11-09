// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"

#include "SGameModeBase.generated.h"

class UEnvQuery;
class UCurveFloat;


/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	//
	FTimerHandle SpawnTimerHandle;
	float SpawnTimeInterval;
	int EnemyNumber;
	int EnemyLimit;
	
	//
	virtual void StartPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> SpawnClass;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float MaxBotCount;
	
	
	UFUNCTION()
	void SpawnTimeEplased();

	UFUNCTION()
	void DoOnQeuryFinish(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

public:
	ASGameModeBase();
};
