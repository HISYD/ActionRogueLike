// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USGameplayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	static bool UpdateDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount);
	
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	static bool ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult);//这里有个逆天情况
	//只用FHitResult&的话，HitResult会作为一个传出参数暴露出来
	//添加const的方式可以帮助我们强调我们不是为了修改传出多个变量，只是引用方式读取节约拷贝开销

	
};
