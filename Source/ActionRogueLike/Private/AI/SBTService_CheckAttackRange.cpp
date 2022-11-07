// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyAIController = OwnerComp.GetAIOwner();
			if (ensure(MyAIController))
			{
				APawn* APawn = MyAIController->GetPawn();
				float Distance = FVector::Distance(APawn->GetActorLocation(), TargetActor->GetActorLocation());
				bool bWithinRange = Distance  < 500.0f;

				bool bHasLos;
				if (bWithinRange)
				{
					bHasLos = MyAIController->LineOfSightTo(TargetActor);
				}

				BlackBoardComp->SetValueAsBool(BBKey.SelectedKeyName, bWithinRange && bHasLos);
			}
		}
	}
}
