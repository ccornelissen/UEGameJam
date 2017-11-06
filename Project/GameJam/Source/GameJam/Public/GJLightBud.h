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
	LB_Used,
	Max
};

class AGJLightBudAI;
class UBoxComponent;
class APowerPad;
class UPaperFlipbookComponent;
class UPaperFlipbook;

UCLASS()
class GAMEJAM_API AGJLightBud : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties//
	AGJLightBud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AGJLightBudAI* MyController = nullptr;

	AActor* FollowPoint = nullptr;

	AActor* MovePoint = nullptr;

	ELightBudState CurrentState = ELightBudState::LB_Dormant;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LightTriggers")
	TArray<UBoxComponent*> LightTriggers;

	UFUNCTION(BlueprintCallable, Category = "LightTriggers")
	void SetupLightTriggers();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	TArray<APowerPad*> PowerPads;

	void ClearPads();

	//Animation books
	UPROPERTY(EditDefaultsOnly, Category = "Sprite")
	UPaperFlipbookComponent* PaperFlipbook = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* WalkLeft;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* WalkRight;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* Idle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ReturnToPlayer();

	void SetFollowPoint(AActor& PointToFollow);

	void SetMovePoint(AActor& PointToMove);

	ELightBudState GetCurrentState();

	void SetCurrentState(ELightBudState StateToSet);
	
};
