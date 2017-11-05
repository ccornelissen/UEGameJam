// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerPad.generated.h"

UENUM()
enum class EPadState : uint8
{
	PS_Off,
	PS_On,
	Max
};

class APowerPadManager;

UCLASS()
class GAMEJAM_API APowerPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerPad();

	EPadState GetPadState();

	void SetPadState(EPadState StateToSet);

	void SetManager(APowerPadManager& ManagerToSet);

	void TurnOn();

	void TurnOff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	EPadState CurrentPadState = EPadState::PS_Off;

	APowerPadManager* MyManager = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* MyMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UMaterialInterface* OffMat = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UMaterialInterface* OnMat = nullptr;
	
	
};
