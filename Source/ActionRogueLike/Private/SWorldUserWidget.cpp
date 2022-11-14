// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();
		return;
	}

	FVector2D ScreenLocation;
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation(), ScreenLocation))
	{
		const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenLocation /= Scale;
	}
	if (ParentBox)
	{
		ParentBox->SetRenderTranslation(ScreenLocation);
	}
	
}
