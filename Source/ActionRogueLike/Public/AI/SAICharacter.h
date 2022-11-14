// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "SWorldUserWidget.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USAttributeComponent;
class UPawnSensingComponent;


UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

protected:
	USWorldUserWidget* ActiveHealthBar;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;
	
	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttribComp;
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* SenseComp;
	
	FName TimeToHitParamName;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void DoOnSeePawn(APawn* Pawn);

	UFUNCTION()
	void DoOnHealthChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	
	virtual void PostInitializeComponents() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

};
