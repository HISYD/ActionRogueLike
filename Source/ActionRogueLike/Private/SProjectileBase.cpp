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
	SphereComp->SetSphereRadius(15.0f);
	

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

//在beginplay里面添加了一个忽视发射者的函数。之前放在构造器里面分分钟报错，要注意类比蓝图，写在蓝图里面的都是用事件去关联的，beginplay和tick都是提供了函数，其他可以统一写在后初始化里面绑定事件
void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}
void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();//重写的时候记得调用父类的函数
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
}



//Function
//做了分离，OnActorHit作为一个纯粹的调用者，再去调用explode
void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GetInstigator() != OtherActor)
	{
		Explode();
		
	}
}
//因为用ufuncition把函数暴露在蓝图了，所以实际定义要这么写
void ASProjectileBase::Explode_Implementation()
{
	if(ensure(IsValid(this)))//保护措施，cjc也这么写的
	{
		//worldcontext object 是什么
        UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, GetActorLocation(), GetActorRotation());
		Destroy();
	}
	
}



