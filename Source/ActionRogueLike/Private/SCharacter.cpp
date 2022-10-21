// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

//为什么头文件里面不需要include
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"//对应GetCharacterMovement()，注意是要声明返回的对象的类型对应的头文件，但是为社么不能直接返回该函数所在的头文件？


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


	GetCharacterMovement()->bOrientRotationToMovement = true;//字面意思
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.1f;//下落时允许控制的偏移量
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

	//设定一个关键词，绑定一个函数指针，下文的函数影响移动。在编辑器端projectsetting设置bind将关键词绑定到按键上
	//要求必须取地址用指针的方式将成员传进去
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//教程用的这个，实际上用子类也有这个函数指针，为什么要用父类呢
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	//绑定行为
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);//IE_Pressed是一个枚举类，代表在pressed时才出发，详情f12
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	
}








//自定义函数
void ASCharacter::MoveForward(float value)
{
	//ControlRotation和ActorRotation不一致，被分离了，因此这里要用Rotation而不是ActorForward去做为移动方向
	FRotator ControlRot = GetControlRotation();//
	ControlRot.Pitch = 0.0f;//只需要yaw，清除其他旋转
	ControlRot.Roll = 0.0f;
	

	//AddMovementInput(GetActorForwardVector(), value);//[无视ControlRotation用直直按照ActorForwardVector去MoveForward的代码]
	AddMovementInput(ControlRot.Vector(), value);
}
void ASCharacter::MoveRight(float value)
{
	//这里是为了解决，如果完全基于actor右作为向右的基准，角色会不停原地转
	FRotator ControlRot = GetControlRotation();//
	ControlRot.Pitch = 0.0f;//只需要yaw，清除其他旋转
	ControlRot.Roll = 0.0f;

	//教程讲的好拉跨，用tomato去搜索GetRightVector, 拿到它的代码，不直接调用避免Include，进去拷贝源代码，用于分解一个FRotator拿到right向量
	//XYZ对应前右上
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);


	AddMovementInput(RightVector, value);
}


void ASCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	//FTransform SpawnTM = FTransform(GetControlRotation(), GetActorLocation());
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;//自己f12进去看

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);//<AActor>(类，变换矩阵，参数)
}
