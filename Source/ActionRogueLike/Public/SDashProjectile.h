// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()

	FTimerHandle TimeHandle_TeleportDelay, TimerHandle_ExplodeDelay;

	
	

	// UFUNCTION()
protected:	
	virtual void BeginPlay() override;
	virtual void Explode_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TeleportInstigator();
};
