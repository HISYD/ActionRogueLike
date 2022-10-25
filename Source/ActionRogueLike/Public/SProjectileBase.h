// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class ACTIONROGUELIKE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	

	ASProjectileBase();

	
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* MainEffect;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* TrailEffect;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MoveComp;

	//virtual void PostInitializeComponents() override;

public:	

	virtual void Tick(float DeltaTime) override;
	void OnHitSpawnEffect(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
