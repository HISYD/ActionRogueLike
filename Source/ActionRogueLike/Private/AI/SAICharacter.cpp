// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	
	AttribComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::CheckIfDead);
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


void ASAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASAICharacter::CheckIfDead(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if(NewHealth < 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

