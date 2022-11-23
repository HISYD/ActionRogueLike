// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"

#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}


void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		//TimerHandle如果不在这里创建而在类里面作为成员创建，就不会自动回收了
		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Instigator);
		//在character里面写的时候character类里面自带了GetWorldTimerManager
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);
		
	}

}


void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensure(ProjectileClass))
	{
		FVector CameraLocation, HitLocation;
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		ASCharacter* SInstigatorCharacter = Cast<ASCharacter>(InstigatorCharacter);
		if (SInstigatorCharacter)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;//自己f12进去看
			SpawnParams.Instigator = InstigatorCharacter;//这些参数会送给spawn的对象，这样我们就可以在spawn的内容（攻击魔法）中访问释放者信息，后续教程是通过这种方式在蓝图里面做出释放者碰撞豁免
			
			SInstigatorCharacter->PawnCameraShoot(CameraLocation, HitLocation);
			FRotator const DesiredRotation = FRotationMatrix::MakeFromX(HitLocation - HandLocation).Rotator();
			
			FTransform const SpawnTM = FTransform(DesiredRotation, HandLocation);
			GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
		}
	}
	StopAction(InstigatorCharacter);
}
