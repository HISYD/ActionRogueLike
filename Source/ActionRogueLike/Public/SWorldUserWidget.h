// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "SWorldUserWidget.generated.h"

class USizeBox;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(meta=(BindWidget))
	USizeBox* ParentBox;//其实也可以不用，但可以方便限制血条的max min之类的
	
public:
	UPROPERTY(BlueprintReadOnly, Category="UI")
	AActor* AttachedActor;

	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
