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
	ForceComp->bImpulseVelChange = true;//��ѡ����֪����ɶ�����񲻿������mass��������������ܶ�
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);//��ѡ���ֶ�����CollisionӰ��ķ�Χ��Ĭ�ϵ��ǲ���Ӱ��worlddynamicͨ����


	// �ٸչ����ʱ�򣬻��ߺ��ʼ���׶Σ����󶨶��ǿ��Եģ��� ��ը������ ��Ϊһ����̬����MeshComp��OnComponentHit��
	// ���ڹ��������override PostInitializeComponents()�����࣬����ʣ��һ����.h��������virtual void PostInitializeComponents() override�Ĺ���
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


//��ը������
void ABarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}
