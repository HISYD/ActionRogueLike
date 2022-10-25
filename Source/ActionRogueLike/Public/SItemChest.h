// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
	
#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"
class UStaticMeshComponent;


UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface//继承的时候用Ixxx，判断存在的时候用Uxxxx，执行的时候用Ixxx
{
	GENERATED_BODY()
	
	
public:	

	ASItemChest();
	
	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
	void Interact_Implementation(APawn* InstigatorPawn) override;//因为继承的接口UFunction(BluprintNativeEvent)额外做出要求，所以这边要用Interact_Implement做声明
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)//额外提供了在蓝图里面读取该组件的权限
	UStaticMeshComponent* LibMesh;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
