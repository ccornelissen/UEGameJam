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
class UBoxComponent;

UCLASS()
class GAMEJAM_API AGJPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGJPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/////////Character Components//////////
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* CameraComponent = nullptr;

	///////Light Bud Logic/////////////
	TArray<AGJLightBud*> LightBuds;

	UPROPERTY(EditDefaultsOnly, Category = "LightBud")
	float fFollowAdditive = 80.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LightBud")
	USceneComponent* ThrowPoint = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LightBud")
	UBoxComponent* CollectionBox = nullptr;

	UFUNCTION(BlueprintCallable, Category = "LightBud")
	void SetCollectionBox(UBoxComponent* BoxToSet);

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///////Movement Functions/////////////
	void MoveForward(float Value);
	void MoveRight(float Value);

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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
