// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = 100;
}

void USAttributeComponent::UpdateHealth(int delta)
{
	Health += delta;
}
