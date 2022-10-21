// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"


//手动声明指针是啥，只是为了帮助理解
class UCameraComponent;
class USpringArmComponent;


UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;//[PrimaryAttack函数]提供了一个参数，可以去挂载某个class，让actor可以识别调用某个类，常用于投射物伤害类型等
	//其实也可以用UClass*,但是这个是一个类型安全的模板

public:
	// Sets default values for this character's properties
	ASCharacter();


protected:

	UPROPERTY(VisibleAnywhere)//Macro，为了能够将在实例的Detail中暴露出该Comp
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
