// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

class UStaticMeshComponent;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTargetDummy();
protected:

	UPROPERTY(VisibleAnywhere)//如果comp成员不设置为可见，则绑定函数到子组件的xx事件（adddynamic）会出错会出错
	UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USAttributeComponent* AttribComp;
	UFUNCTION()
	void DoOnHealthChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void BeginPlay() override;
	
public:	

	virtual void Tick(float DeltaTime) override;
};
