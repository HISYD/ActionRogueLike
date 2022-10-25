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
	ForceComp->bImpulseVelChange = true;//可选，不知道干啥，好像不开会根据mass计算冲击波威力大很多
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);//可选，手动设置Collision影响的范围，默认的是不会影响worlddynamic通道的


	// 再刚构造的时候，或者后初始化阶段，做绑定都是可以的，将 爆炸任务函数 作为一个动态绑定在MeshComp的OnComponentHit上
	// 放在构造器里比override PostInitializeComponents()好理解多，并且剩下一个在.h里面声明virtual void PostInitializeComponents() override的功夫
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


//爆炸任务函数
void ABarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}
