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
	ES_Retreating,
	Max
};

class UBoxComponent;
class AGJEnemyAI;
class AGJLightBud;
class UPaperFlipbookComponent;
class UPaperFlipbook;
class ALight;
class UAudioComponent;
class USoundBase;


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

	///////Attack///////

	UPROPERTY(EditAnywhere, Category = "Attack")
	AActor* PortLocation = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float fAttackRange = 10.0f;

	void Attack();

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<ALight> DeathLight;
		
	//Animation books
	UPROPERTY(EditDefaultsOnly, Category = "Sprite")
	UPaperFlipbookComponent* PaperFlipbook = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sprite")
	UPaperFlipbookComponent* DizzyFlipbook = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* WalkAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* AttackAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* IdleAnim;

	//Audio
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* MyAudioComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* BiteSound;
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* RetreatSound;

	//ParticleSystem
	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	TSubclassOf<AActor> MyParticle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Stun(float StunForce);

	////Death/////
	UPROPERTY(EditAnywhere, Category = "Retreat")
	AActor* RetreatLocation = nullptr;

	void Retreat();

	UPROPERTY(EditAnywhere, Category = "Patrol")
	TArray<AActor*> PatrolPoints;
	
};
