// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GJUserWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UEditableTextBox;

UCLASS()
class GAMEJAM_API UGJUserWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	void SetInteractionText(FText TextToSet);
	void SetTutorialText(FText TextToSet, float fTimer);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Player UI")
	UTextBlock* InteractionText = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Player UI")
	UTextBlock* TutorialText = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Player UI")
	void SetupUIElements(UTextBlock* InteractText, UTextBlock* TutText);

	UPROPERTY(EditDefaultsOnly, Category = "Player UI")
	float fTutorialTimer = 5.0f;

	void ClearTutorialText();

	FTimerHandle TutHandle;

	FText ZeroText;


	

	
	
	
};
