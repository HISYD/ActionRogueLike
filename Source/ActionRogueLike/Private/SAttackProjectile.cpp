// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttackProjectile.h"

#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"



void ASAttackProjectile::PostInitializeComponents()
{
	ASProjectileBase::PostInitializeComponents();//不用父类base的hit特性》？
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASAttackProjectile::OnActorOverlap);
}

void ASAttackProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(ensure(AttributeComponent))
		{
			AttributeComponent->UpdateHealth(-20);
			Destroy();
		}
	}
}
