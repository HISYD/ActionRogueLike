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
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	
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
	
	UFUNCTION()//必须声明，如果需要绑定的话
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);//声明为virtual，未来可能要修改hit的调用内容
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
	
};
