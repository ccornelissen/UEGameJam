// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GJLightBud.generated.h"

UENUM()
enum class ELightBudState : uint8
{
	LB_Dormant,
	LB_Following,
	LB_Aiming,
	Max
};

class AGJLightBudAI;

UCLASS()
class GAMEJAM_API AGJLightBud : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGJLightBud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AGJLightBudAI* MyController = nullptr;

	AActor* FollowPoint = nullptr;

	ELightBudState CurrentState = ELightBudState::LB_Dormant;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ReturnToPlayer();

	void SetFollowPoint(AActor& PointToFollow);

	ELightBudState GetCurrentState();

	void SetCurrentState(ELightBudState StateToSet);


	
	
};
