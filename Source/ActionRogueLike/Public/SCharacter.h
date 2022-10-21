// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


//�ֶ�����ָ����ɶ��ֻ��Ϊ�˰������
class UCameraComponent;
class USpringArmComponent;


UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;//[PrimaryAttack����]�ṩ��һ������������ȥ����ĳ��class����actor����ʶ�����ĳ���࣬������Ͷ�����˺����͵�
	//��ʵҲ������UClass*,���������һ�����Ͱ�ȫ��ģ��

public:
	// Sets default values for this character's properties
	ASCharacter();


protected:

	UPROPERTY(VisibleAnywhere)//Macro��Ϊ���ܹ�����ʵ����Detail�б�¶����Comp
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp; 

	void MoveForward(float value);
	void MoveRight(float value);
	//void Jump(float value);
	void PrimaryAttack();


	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
