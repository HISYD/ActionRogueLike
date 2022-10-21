// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

//Ϊʲôͷ�ļ����治��Ҫinclude
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"//��ӦGetCharacterMovement()��ע����Ҫ�������صĶ�������Ͷ�Ӧ��ͷ�ļ�������Ϊ��ô����ֱ�ӷ��ظú������ڵ�ͷ�ļ���


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


	GetCharacterMovement()->bOrientRotationToMovement = true;//������˼
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.1f;//����ʱ������Ƶ�ƫ����
}



void ASCharacter::BeginPlay()
{
	
	Super::BeginPlay();
	
}
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//�趨һ���ؼ��ʣ���һ������ָ�룬���ĵĺ���Ӱ���ƶ����ڱ༭����projectsetting����bind���ؼ��ʰ󶨵�������
	//Ҫ�����ȡ��ַ��ָ��ķ�ʽ����Ա����ȥ
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//�̳��õ������ʵ����������Ҳ���������ָ�룬ΪʲôҪ�ø�����
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	//����Ϊ
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);//IE_Pressed��һ��ö���࣬������pressedʱ�ų���������f12
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	
}








//�Զ��庯��
void ASCharacter::MoveForward(float value)
{
	//ControlRotation��ActorRotation��һ�£��������ˣ��������Ҫ��Rotation������ActorForwardȥ��Ϊ�ƶ�����
	FRotator ControlRot = GetControlRotation();//
	ControlRot.Pitch = 0.0f;//ֻ��Ҫyaw�����������ת
	ControlRot.Roll = 0.0f;
	

	//AddMovementInput(GetActorForwardVector(), value);//[����ControlRotation��ֱֱ����ActorForwardVectorȥMoveForward�Ĵ���]
	AddMovementInput(ControlRot.Vector(), value);
}
void ASCharacter::MoveRight(float value)
{
	//������Ϊ�˽���������ȫ����actor����Ϊ���ҵĻ�׼����ɫ�᲻ͣԭ��ת
	FRotator ControlRot = GetControlRotation();//
	ControlRot.Pitch = 0.0f;//ֻ��Ҫyaw�����������ת
	ControlRot.Roll = 0.0f;

	//�̳̽��ĺ����磬��tomatoȥ����GetRightVector, �õ����Ĵ��룬��ֱ�ӵ��ñ���Include����ȥ����Դ���룬���ڷֽ�һ��FRotator�õ�right����
	//XYZ��Ӧǰ����
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);


	AddMovementInput(RightVector, value);
}


void ASCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	//FTransform SpawnTM = FTransform(GetControlRotation(), GetActorLocation());
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;//�Լ�f12��ȥ��

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);//<AActor>(�࣬�任���󣬲���)
}
