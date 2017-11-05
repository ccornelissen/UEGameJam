// Fill out your copyright notice in the Description page of Project Settings.

#include "GJPlayerController.h"
#include "GJUserWidget.h"

void AGJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Setup player UI
	if (PlayerUIToCreate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Creating UI"));

		PlayerUI = CreateWidget<UGJUserWidget>(this, PlayerUIToCreate);

		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetHideCursorDuringCapture(false);

		PlayerUI->AddToViewport(9999);
	}

	bShowMouseCursor = true;
}
