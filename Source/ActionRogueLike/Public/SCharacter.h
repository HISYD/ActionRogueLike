// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


//�ֶ�����ָ����ɶ��ֻ��Ϊ�˰������
class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;

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

	FTimerHandle TimerHandle_PrimaryAttack;//Ϊ���������ṩ�ļ�ʱ���
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
	
	
	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PrimaryInteract();
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
