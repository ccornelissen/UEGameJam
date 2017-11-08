// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GJPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPaperFlipbookComponent;
class UPaperFlipbook;
class AGJLightBud;
class AGJAimActor;
class UBoxComponent;
class UGJUserWidget;
class AGJPlayerController;
class UAudioComponent;
class USoundBase;


UCLASS()
class GAMEJAM_API AGJPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties//
	AGJPlayer();

	UFUNCTION(BlueprintCallable, Category = "Tutorial")
	void SetTutorial(FText InText, float fTimer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/////////Character Components//////////
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* CameraComponent = nullptr;

	AGJPlayerController* MyController = nullptr;

	/////////Audio//////////

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	UAudioComponent* MyAudioComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* OrderSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* KickSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* RecallSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* DiscoverSound;

	///////Light Bud Logic/////////////
	TArray<AGJLightBud*> LightBuds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LightBud")
	UBoxComponent* CollectionBox = nullptr;

	UFUNCTION(BlueprintCallable, Category = "LightBud")
	void SetCollectionBox(UBoxComponent* BoxToSet);

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void RecallBuds();

	void RearrangeBuds();

	void SwitchBudForward();

	//////Aiming Logic///////
	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	TSubclassOf<AGJAimActor> AimingActor;

	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	TSubclassOf<AGJAimActor> MoveToActor;

	AGJAimActor* AimActor = nullptr;

	bool bAiming = false;

	void StartAiming();

	void StopAiming();

	void AimBud();

	void OrderBud();

	void SetBudFollow(AGJLightBud& CurBud);

	int32 iCurrentBud = 0;

	////////Kicking//////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Kick")
	UBoxComponent* KickBox = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Kick")
	void SetKickBox(UBoxComponent* BoxToSet);

	UPROPERTY(EditDefaultsOnly, Category = "Kick")
	float fKickTimer = 1.0f;

	FTimerHandle KickHandle;

	bool bCanKick = true;

	bool bKicking = false;

	UPROPERTY(EditDefaultsOnly, Category = "Kick")
	float fKickDistance = 50.0f;

	void Kick();

	void ResetKick();

	///////Movement Functions/////////////
	void MoveForward(float Value);
	void MoveRight(float Value);

	//Animation books
	UPROPERTY(EditDefaultsOnly, Category = "Sprite")
	UPaperFlipbookComponent* PaperFlipbook = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* WalkAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* PointAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* IdleAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* KickAnim;

	bool bAnimSwitch = true;

	void ResetAnim();

	FTimerHandle AnimHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float fAnimTimer = 1.0f;

	/////UI//////
	UGJUserWidget* MyWidget = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RemoveLightBud(int32 iNum);
	
	
};
