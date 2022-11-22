// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"

class USAction;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

//SActionComponent 目的是为了管理和存储一系列的SAction
class ACTIONROGUELIKE_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USActionComponent();
	
	UFUNCTION(BlueprintCallable, Category="Action")
	void AddAction(TSubclassOf<USAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category="Action")
	bool StartActionByName(AActor* Instigator, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category="Action")
	bool StopActionByName(AActor* Instigator, FName ActionName);


	
protected:

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<USAction>> DefaultActions;
	
	UPROPERTY()
	TArray<USAction*> Actions;
	
	virtual void BeginPlay() override;

	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};