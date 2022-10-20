// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

//Ϊʲôͷ�ļ����治��Ҫinclude
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//����һϵ��comp���ҹ��ظ��ӹ�ϵ
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	//�޸�character��yaw�ɿ���Ĭ��ֵ������springarm�ĵ�����ת����
	bUseControllerRotationYaw = false;//������Զ����
	SpringArmComp->bUsePawnControlRotation = true;//���������������spring������֧�ֿ���

}

//�Զ��庯��
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

	//�趨һ���ؼ��ʣ���һ������ָ�룬���ĵĺ���Ӱ���ƶ����ڱ༭����projectsetting����bind���ؼ��ʰ󶨵�������
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//�̳��õ������ʵ����������Ҳ���������ָ�룬ΪʲôҪ�ø�����
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

