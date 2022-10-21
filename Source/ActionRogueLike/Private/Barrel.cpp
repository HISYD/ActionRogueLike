// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrel.h"
#include "Components\StaticMeshComponent.h"
#include "PhysicsEngine\RadialForceComponent.h"

// Sets default values
ABarrel::ABarrel()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComp;
	MeshComp->SetCollisionProfileName("PhysicsActor");
	MeshComp->SetSimulatePhysics(true);
	

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("Radial Force");
	ForceComp->SetupAttachment(MeshComp);
	




	// Leaving this on applies small constant force via component 'tick' (Optional)
	ForceComp->SetAutoActivate(false);

	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	ForceComp->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

	// Binding either in constructor or in PostInitializeComponents() below
	//MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABarrel::PostInitializeComponents()
{
	// Don't forget to call parent function
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &ABarrel::OnActorHit);
}


//void ABarrel::OnActorHit()
void ABarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}
