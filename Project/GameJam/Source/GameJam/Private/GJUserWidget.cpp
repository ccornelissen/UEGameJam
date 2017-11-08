 // Fill out your copyright notice in the Description page of Project Settings.

#include "GJUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

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
	if (TutorialText && TutTextBG)
	{
		TutorialText->SetText(TextToSet);

		TutorialText->SetVisibility(ESlateVisibility::Visible);

		TutTextBG->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(TutHandle, this, &UGJUserWidget::ClearTutorialText, fTimer, false);
	}
}

void UGJUserWidget::SetupUIElements(UTextBlock* InteractText, UTextBlock* TutText, UImage* BGImage)
{
	if (InteractText && TutText && BGImage)
	{
		InteractionText = InteractText;

		TutorialText = TutText;

		TutTextBG = BGImage;
	}
}

void UGJUserWidget::ClearTutorialText()
{
	if (TutorialText)
	{
		TutorialText->SetText(ZeroText);

		TutorialText->SetVisibility(ESlateVisibility::Hidden);

		TutTextBG->SetVisibility(ESlateVisibility::Hidden);
	}
}


