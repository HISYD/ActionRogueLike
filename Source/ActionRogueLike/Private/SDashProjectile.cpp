// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "AITypes.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework\PlayerController.h"


#include "SDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Sound/SoundCue.h"

void ASDashProjectile::BeginPlay()
{
	ASProjectileBase::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_ExplodeDelay, this, &ASDashProjectile::Explode, 1.2f);
}

void ASDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_ExplodeDelay);
	UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, GetActorLocation(), GetActorRotation());
	GetWorldTimerManager().SetTimer(TimeHandle_TeleportDelay, this, &ASDashProjectile::TeleportInstigator, 0.1f);

	MainEffect->DeactivateSystem();
	TrailEffect->DeactivateSystem();
	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);
}

void ASDashProjectile::TeleportInstigator_Implementation()
{
	APawn* InstigatorPawn = Cast<APawn>(GetInstigator());
	APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
	if (ensure(InstigatorPawn))
	{
		FRotator NowRotation = InstigatorPawn->GetActorRotation();
		InstigatorPawn->TeleportTo(GetActorLocation(), NowRotation);
		Destroy();
	}
}
