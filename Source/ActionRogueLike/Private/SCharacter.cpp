// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

//为什么头文件里面不需要include
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建一系列comp并且挂载父子关系
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	//修改character的yaw可控性默认值，设置springarm的单独旋转控制
	bUseControllerRotationYaw = false;//避免永远背对
	SpringArmComp->bUsePawnControlRotation = true;//单独允许子组件（spring）单独支持控制

}

//自定义函数
void ASCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void ASCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//设定一个关键词，绑定一个函数指针，下文的函数影响移动。在编辑器端projectsetting设置bind将关键词绑定到按键上
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//教程用的这个，实际上用子类也有这个函数指针，为什么要用父类呢
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

