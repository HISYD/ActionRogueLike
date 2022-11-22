// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"
#include "SAttributeComponent.h"

bool USGameplayFunctionLibrary::UpdateDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	USAttributeComponent* AttribComp = USAttributeComponent::GetAttribute(TargetActor);
	if (AttribComp)
	{
		return AttribComp->UpdateHealth(DamageAmount);
	}
	return false;
	
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if (UpdateDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();//这里说明，我们必须击中Mesh组件，因为只有Mesh有仿真和骨骼。但是Capsule碰撞组件会提前block掉
		//因此我们必须新建一个Projectile通道，设置Capsule-Ignore，Mesh-Overlap
		if (HitComp && HitComp->IsSimulatingPhysics((HitResult.BoneName)))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 3000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}
	return false;
}
