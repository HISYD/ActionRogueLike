// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ABarrel : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ABarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;


	virtual void PostInitializeComponents() override;


	// Must be marked with ufunction in order to 'bind' the event
	UFUNCTION()
	void OnActorHit();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
