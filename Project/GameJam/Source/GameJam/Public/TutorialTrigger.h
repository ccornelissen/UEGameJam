// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TutorialTrigger.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API ATutorialTrigger : public ATriggerBox
{
	GENERATED_BODY()

	ATutorialTrigger();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial")
	FText TutorialText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tutorial")
	float fTimer = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial")
	bool bCanShowTut = true;
};
