// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerPadManager.generated.h"

class APowerPad;
class ALight;
class UAudioComponent;
class AGJEnemy;

UCLASS()
class GAMEJAM_API APowerPadManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerPadManager();

	void PadCheck();

	void ActionComplete();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bAllPadsEnabled = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pads")
	TArray<APowerPad*> PowerPads;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	bool bHasDoorToOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	AActor* DoorToMove = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	AActor* NewDoorLocation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	bool bHasLightsToTurnOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	TArray<ALight*> LightsToTurnOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	bool bHasEnemyToScare = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal")
	TArray<AGJEnemy*> EnemiesToScare;

	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* MyAudioComp = nullptr;


};
