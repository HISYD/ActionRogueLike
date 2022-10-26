// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


//�ֶ�����ָ����ɶ��ֻ��Ϊ�˰������
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
	TSubclassOf<AActor> ProjectileClass;//[PrimaryAttack����]�ṩ��һ������������ȥ����ĳ��class����actor����ʶ�����ĳ���࣬������Ͷ�����˺����͵�
	//��ʵҲ������UClass*,���������һ�����Ͱ�ȫ��ģ��

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnim;//�����TSubclassOf<>ģ�巴���ᱨ��

	UPROPERTY(EditAnywhere, Category="Dash")
	TSubclassOf<AActor> DashProjectile;
	UPROPERTY(EditAnywhere, Category="Dash")
	UAnimMontage* DashAnim;
	
	FTimerHandle TimerHandle_PrimaryAttack, TimerHandle_PrimaryDash;//Ϊ���������ṩ�ļ�ʱ���



	
public:
	// Sets default values for this character's properties
	ASCharacter();


protected:

	UPROPERTY(VisibleAnywhere)//Macro��Ϊ���ܹ�����ʵ����Detail�б�¶����Comp
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

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
