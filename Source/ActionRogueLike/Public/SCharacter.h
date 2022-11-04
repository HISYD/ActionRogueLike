// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


//????????????????????????????
class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<AActor> ProjectileClass;//[PrimaryAttack????]?????????????????????????class????actor??????????????????????????????????
	//??????????UClass*,???????????????????????

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;//?????TSubclassOf<>??°Í??????

	UPROPERTY(EditAnywhere, Category="Dash")
	TSubclassOf<AActor> DashProjectile;
	UPROPERTY(EditAnywhere, Category="Dash")
	UAnimMontage* DashAnim;
	
	FTimerHandle TimerHandle_PrimaryAttack, TimerHandle_PrimaryDash;//??????????????????



	
public:
	// Sets default values for this character's properties
	ASCharacter();


protected:

	UPROPERTY(VisibleAnywhere)//Macro?????????????????Detail?§Ò??????Comp
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp; 
	
	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USAttributeComponent* AttributeComp;
	
	
	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PrimaryDash();
	void PrimaryDash_TimeElapsed();
	void PrimaryInteract();
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void CheckIfDead(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
