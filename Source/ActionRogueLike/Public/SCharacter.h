// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


//????????????????????????????
class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;
class USActionComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category="Dash")
	TSubclassOf<AActor> DashProjectile;
	UPROPERTY(EditAnywhere, Category="Dash")
	UAnimMontage* DashAnim;
	
	FTimerHandle TimerHandle_PrimaryAttack, TimerHandle_PrimaryDash;//??????????????????



	
public:
	// Sets default values for this character's properties
	ASCharacter();


protected:

	UPROPERTY(VisibleAnywhere)//Macro?????????????????Detail?????????Comp
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp; 
	
	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USActionComponent* ActionComp;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PrimaryDash();
	void PrimaryDash_TimeElapsed();
	void PrimaryInteract();

	void SprintStart();
	void SprintStop();


	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void CheckIfDead(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)//×÷±×ÂëÒ®£¡
	void HealSelf(float Amount);
};
