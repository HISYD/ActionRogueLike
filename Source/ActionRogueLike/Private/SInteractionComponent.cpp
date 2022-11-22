// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"
#include "Camera\CameraComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USInteractionComponent::PrimaryInteract()
{
	//配置参数
	AActor* MyOwner = GetOwner();
	UCameraComponent* CameraComp = Cast<UCameraComponent>(MyOwner->GetComponentByClass(UCameraComponent::StaticClass()));
	FVector EyeLocation = CameraComp->GetComponentLocation();
	FRotator EyeRotation = CameraComp->GetComponentRotation();

	FVector EndLocation = EyeLocation+EyeRotation.Vector()*600;

	//获取视线请求结果
	FHitResult OnHitResult;
	FCollisionObjectQueryParams ObjQueryParams;
	ObjQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	GetWorld()->LineTraceSingleByObjectType(OnHitResult, EyeLocation, EndLocation, ObjQueryParams);//或许可以理解为，从“世界”的视角去计算的方法都放在world里，通过getworld去得到一个指针进行箭头访问

	//没有实际使用的，获取实现请求结果，此处做演示
	TArray<FHitResult> OnHitResults;
	FCollisionShape Shape;
	Shape.SetSphere(30.0f);
	GetWorld()->SweepMultiByObjectType(OnHitResults, EyeLocation, EndLocation, FQuat::Identity, ObjQueryParams, Shape);//用shape去做sweep，发生overlap会被记录下来，支持记录连续的多个hit结果，没有实际用，就是演示下
	for (FHitResult Hit : OnHitResults)
	{
		AActor* HitActor = Hit.GetActor();
		//后面同下
	}

	//若hit的actor存在指定接口，则执行接口行为
	AActor* HitActor = OnHitResult.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<USGameplayInterface>())
		{
			APawn* MyOwnerPawn = Cast<APawn>(GetOwner());
			ISGameplayInterface::Execute_Interact(HitActor, MyOwnerPawn);
			//ISGameplayInterface::Execute_Interact(HitActor, GetOwner());//这句话有语法错误，owner不一定是pawn，必须用受保护的cast去做转换
		}
	}

	DrawDebugLine(GetWorld(), EyeLocation, EndLocation, FColor::Red, false, 2.0f, 0, 2.0f);
}

