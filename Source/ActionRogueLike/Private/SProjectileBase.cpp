// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");
	

	MainEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MainEffect"));
	MainEffect->SetupAttachment(RootComponent);
	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
	TrailEffect->SetupAttachment(RootComponent);
	
	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));
	MoveComp->InitialSpeed = 1500.0f;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;

	
}


void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASProjectileBase::OnHitSpawnEffect(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, Hit.Location, NormalImpulse.Rotation());
	DrawDebugSphere(GetWorld(), Hit.Location, 50, 8, FColor::Red, false, 10, 0, 2);
}