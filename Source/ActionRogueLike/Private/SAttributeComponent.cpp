// Fill out your copyright notice in the Description page of Project Settings.




#include "SAttributeComponent.h"
#include "SGameModeBase.h"


static TAutoConsoleVariable<float> DamageMultiplier(TEXT("DamageMultiplier"), 1.0f, TEXT("Damage Multiplier"),  ECVF_Cheat);


USAttributeComponent* USAttributeComponent::GetAttribute(AActor* AActor)
{
	USAttributeComponent* AttribComp = Cast<USAttributeComponent>(AActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (ensure(AttribComp))
	{
		return AttribComp;
	}
	return nullptr;
}

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = 100.0f;
}

bool USAttributeComponent::UpdateHealth(int delta)
{
	delta *= DamageMultiplier.GetValueOnGameThread();
	Health += delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, delta);

	if (Health <= 0.0f && delta < 0.0f)
	{
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GM)
		{
			GM->DoOnActorKilled(GetOwner());
		}
	}
	return true;	
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}
 