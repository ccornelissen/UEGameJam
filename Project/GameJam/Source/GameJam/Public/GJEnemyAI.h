// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GJEnemyAI.generated.h"

class UBlackboardComponent;
class AGJLightBud;
/**
 * 
 */
UCLASS()
class GAMEJAM_API AGJEnemyAI : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetLightBud(AActor* ActorToSet);

	void SetRetreatPoint(AActor* ActorToSet);

	void SetStunned(bool ToSet);

	void ClearLightBud();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "AI")
	UBlackboardComponent* MyBlackBoard = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LightBudKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName RetreatPointKeyName;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName StunKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName FalseKeyName;

};
