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

	void DestroyAimActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	USphereComponent* SphereCollider;
};
