// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GJAimActor.generated.h"

class USphereComponent;

UCLASS()
class GAMEJAM_API AGJAimActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGJAimActor();

	USphereComponent* GetSphereComp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DestroyAimActor();

	FTimerHandle LifeSpanTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	USphereComponent* SphereCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Life")
	float fLifeSpan = 0.3f;

	
	
};
