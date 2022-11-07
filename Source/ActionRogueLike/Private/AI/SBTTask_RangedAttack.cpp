// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (ensure(Controller))
	{
		ACharacter* MyPawn = Cast<ACharacter>(Controller->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		FVector SpawnLocation = MyPawn->GetMesh()->GetSocketLocation("FX_Gun_Barrel");

		UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
		AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		
		FVector Direction = TargetActor->GetActorLocation() - SpawnLocation;
		FRotator Rotation = Direction.Rotation();

		FActorSpawnParameters SpawnParas;
		SpawnParas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(Projectile, SpawnLocation, Rotation, SpawnParas);//如果不使用<>会报错，有点难理解，或许可以理解为使用了Tsubclass

		return NewProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
