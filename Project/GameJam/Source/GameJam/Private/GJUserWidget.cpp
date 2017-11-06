 // Fill out your copyright notice in the Description page of Project Settings.

#include "GJUserWidget.h"
#include "Components/TextBlock.h"

void UGJUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGJUserWidget::SetInteractionText(FText TextToSet)
{
	if (InteractionText)
	{

	}
}

void UGJUserWidget::SetTutorialText(FText TextToSet, float fTimer)
{
	if (TutorialText)
	{
		TutorialText->SetText(TextToSet);

		TutorialText->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(TutHandle, this, &UGJUserWidget::ClearTutorialText, fTimer, false);
	}
}

void UGJUserWidget::SetupUIElements(UTextBlock* InteractText, UTextBlock* TutText)
{
	if (InteractText && TutText)
	{
		InteractionText = InteractText;

		TutorialText = TutText;
	}
}

void UGJUserWidget::ClearTutorialText()
{
	if (TutorialText)
	{
		TutorialText->SetText(ZeroText);

		TutorialText->SetVisibility(ESlateVisibility::Hidden);
	}
}


