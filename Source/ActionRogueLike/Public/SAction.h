// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.generated.h"


class UWorld;


UCLASS(Blueprintable)//允许该C++类派生蓝图类
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);
	
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);
	
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;

	virtual UWorld* GetWorld() const override;
	//不重写也是可以用的，但是如果不做重写，那么蓝图内getworld后将不会提供像别的actor那样的丰富的在真实世界的功能函数例如spawn
	
};
