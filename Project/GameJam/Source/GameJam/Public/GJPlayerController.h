// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GJPlayerController.generated.h"

class UGJUserWidget;
/**
 * 
 */
UCLASS()
class GAMEJAM_API AGJPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UGJUserWidget& GetUserWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	UGJUserWidget* PlayerUI = nullptr;

protected:

	// Called when the game starts or when spawned//
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGJUserWidget> PlayerUIToCreate = nullptr;
	
};
