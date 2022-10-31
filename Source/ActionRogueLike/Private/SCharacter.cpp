// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"//��ӦGetCharacterMovement()��ע����Ҫ�������صĶ�������Ͷ�Ӧ��ͷ�ļ�������Ϊ��ô����ֱ�ӷ��ظú������ڵ�ͷ�ļ���

#include "DrawDebugHelpers.h"

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

	//������comp
	InteractionComp = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp"));
	AttributeComp   = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));
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

	//PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &InteractionComp->PrimaryInteract);//�������䣬ֻ����󶨽�ɫ����ĺ���
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("PrimaryDash", IE_Pressed, this, &ASCharacter::PrimaryDash);
	
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::CheckIfDead);
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


void ASCharacter::PrimaryAttack()//�������������Ź������������Ҽ�ʱ������ȷʱ�����������Ĺ�������spawnħ��
{
	PlayAnimMontage(AttackAnim);//���Ż��ֶ�����
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);//ʹ��ָ�������ʱ���ӳ�0.2�룬�ȴ��ֲ������˶�����ȷλ�òź󴥷��湥������
}
void ASCharacter::PrimaryAttack_TimeElapsed()//�����Ĺ���������ʩ��ħ��
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	//FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;//�Լ�f12��ȥ��
	SpawnParams.Instigator = this;//��Щ�������͸�spawn�Ķ����������ǾͿ�����spawn�����ݣ�����ħ�����з����ͷ�����Ϣ�������̳���ͨ�����ַ�ʽ����ͼ���������ͷ�����ײ����

	FRotator CameraRotator = CameraComp->GetComponentRotation();
	FVector CameraBegin = CameraComp->GetComponentLocation();
	FVector CameraEnd   = CameraBegin + 2000 * CameraRotator.Vector();
	
	FHitResult CameraHitResult;
	GetWorld()->LineTraceSingleByChannel(CameraHitResult, CameraBegin, CameraEnd, ECollisionChannel::ECC_Camera);
	FVector DesiredLocation = CameraHitResult.IsValidBlockingHit() ? CameraHitResult.Location : CameraEnd;
	FRotator DesiredRotator = (DesiredLocation - HandLocation).Rotation();//��ģ������������任��ȥ��ŷ������ô��ǰ��������һֱ����lookat
	FTransform SpawnTM = FTransform(DesiredRotator, HandLocation);


	//DrawDebugLine(GetWorld(), CameraBegin, DesiredLocation, FColor::Green, false, 2, 0, 2.0f);
	//DrawDebugLine(GetWorld(), HandLocation, DesiredLocation, FColor::Blue, false, 2, 0, 2.0f);
	
	

	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);//<AActor>(�࣬�任���󣬲���),�ȴ�������������ٸ�����Ҫ�Ĳ�������
}

void ASCharacter::PrimaryDash()
{
	PlayAnimMontage(DashAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryDash, this, &ASCharacter::PrimaryDash_TimeElapsed, 0.2f);
	
}
void ASCharacter::PrimaryDash_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	//FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;//�Լ�f12��ȥ��
	SpawnParams.Instigator = this;//��Щ�������͸�spawn�Ķ����������ǾͿ�����spawn�����ݣ�����ħ�����з����ͷ�����Ϣ�������̳���ͨ�����ַ�ʽ����ͼ���������ͷ�����ײ����

	FRotator CameraRotator = CameraComp->GetComponentRotation();
	FVector CameraBegin = CameraComp->GetComponentLocation();
	FVector CameraEnd   = CameraBegin + 2000 * CameraRotator.Vector();
	
	FHitResult CameraHitResult;
	GetWorld()->LineTraceSingleByChannel(CameraHitResult, CameraBegin, CameraEnd, ECollisionChannel::ECC_Camera);
	FVector DesiredLocation = CameraHitResult.IsValidBlockingHit() ? CameraHitResult.Location : CameraEnd;
	FRotator DesiredRotator = (DesiredLocation - HandLocation).Rotation();//��ģ������������任��ȥ��ŷ������ô��ǰ��������һֱ����lookat
	FTransform SpawnTM = FTransform(DesiredRotator, HandLocation);


	GetWorld()->SpawnActor<AActor>(DashProjectile, SpawnTM, SpawnParams);//<AActor>(�࣬�任���󣬲���),�ȴ�������������ٸ�����Ҫ�Ĳ�������
}


void ASCharacter::PrimaryInteract()
{
	if(InteractionComp)//���������д��
	{
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacter::CheckIfDead(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(NewHealth < 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}
