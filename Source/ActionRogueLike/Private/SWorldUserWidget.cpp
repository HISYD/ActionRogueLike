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
	bool bIsOnScreen =UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation(), ScreenLocation); 
	if (bIsOnScreen)
	{
		const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenLocation /= Scale;
	}
	if (ParentBox)
	{
		ParentBox->SetRenderTranslation(ScreenLocation);
	}
	if (ParentBox)
	{
		ParentBox->SetVisibility(bIsOnScreen ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
	
}
