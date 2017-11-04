// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GJLightBudAI.generated.h"

class UBlackboardComponent;
/**
 * 
 */
UCLASS()
class GAMEJAM_API AGJLightBudAI : public AAIController
{
	GENERATED_BODY()
	
public:
	void SetFollowActor(AActor* ActorToSet);

	void SetMoveToActor(AActor* ActorToSet);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "AI")
	UBlackboardComponent* MyBlackBoard = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName FollowKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName MoveToName;
};
