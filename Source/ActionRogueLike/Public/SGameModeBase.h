// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"

#include "SGameModeBase.generated.h"

class UEnvQuery;
class UCurveFloat;
class USSaveGame;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	//
	FString SlotName;
	
	UPROPERTY()
	USSaveGame* CurrentSaveGame;

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

	UFUNCTION()
	void RespawnPlayerElapsed(AController* controller);

public:

	virtual void DoOnActorKilled(AActor* VictimActor);

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	UFUNCTION(BlueprintCallable, Category="SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();//不修饰为UFUNCTION,为了尽可能快
	
	
	ASGameModeBase();
};
