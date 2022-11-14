// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "SWorldUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AttribComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttribComp"));
	AttribComp->Health = 5;
	SenseComp  = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SenseComp"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;//不加这个的话spawn的人物是没有ai的
	TimeToHitParamName = "TimeToHit";
	
}


void ASAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents(); 
	
	AttribComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::DoOnHealthChange);
	SenseComp->OnSeePawn.AddDynamic(this, &ASAICharacter::DoOnSeePawn);
}


void ASAICharacter::DoOnSeePawn(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BB = AIController->GetBlackboardComponent();
		BB->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}

void ASAICharacter::DoOnHealthChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)//击杀布娃娃效果的实现，注意要在ProjectSetting中设置启用碰撞，否则会直接因为下沉坠落
{
	//
	if (ActiveHealthBar == nullptr && HealthBarWidgetClass != nullptr)
	{
		ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
		if (ActiveHealthBar)
		{
			ActiveHealthBar->AttachedActor = this;
			ActiveHealthBar->AddToViewport();	
		}
	}


	//
	if (Delta < 0)
	{
		//Hit Feedback
		//GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
		
		
		//Dead Check
		if (NewHealth < 0)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Healt <0 Killed");

				GetMesh()->SetAllBodiesSimulatePhysics(true);
				GetMesh()->SetCollisionProfileName("Ragdoll");//当然也可以直接在ProjectSetting里面改CharacterMesh的碰撞预设为Query&Physics,但是那样太浪费了。只需要运行时修改切换别的预设就好了
				SetLifeSpan(10.0f);//十秒后销毁
			}
		}
	}
}


void ASAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


