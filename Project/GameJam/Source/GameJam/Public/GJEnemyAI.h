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
	
public:
	void SetLightBud(AActor* ActorToSet);

	void ClearLightBud();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "AI")
	UBlackboardComponent* MyBlackBoard = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LightBudKeyName;
	
};
