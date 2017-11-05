// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GJEnemy.generated.h"

UENUM()
enum class EEnemyState : uint8
{
	ES_Dormant,
	ES_Chasing,
	ES_Stunned,
	Max
};

class UBoxComponent;
class AGJEnemyAI;
class AGJLightBud;

UCLASS()
class GAMEJAM_API AGJEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGJEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///////Trigger Zone///////

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TriggerZone")
	UBoxComponent* TriggerZone = nullptr;

	UFUNCTION(BlueprintCallable, Category = "TriggerZone")
	void SetupTriggerZone();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	AGJEnemyAI* MyController = nullptr;

	AGJLightBud* LightBud = nullptr;

	///////Stunning///////

	FTimerHandle StunHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Stun")
	float fStunTimer = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stun")
	float fPersueDistance = 100.0f;

	EEnemyState CurrentState = EEnemyState::ES_Dormant;

	void RangeCheck();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Stun(float StunForce);
	
};
