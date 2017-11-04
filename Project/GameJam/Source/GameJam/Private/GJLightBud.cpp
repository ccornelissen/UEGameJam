// Fill out your copyright notice in the Description page of Project Settings.

#include "GJLightBud.h"
#include "GJLightBudAI.h"


// Sets default values
AGJLightBud::AGJLightBud()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGJLightBud::BeginPlay()
{
	Super::BeginPlay();
	
	MyController = Cast<AGJLightBudAI>(GetController());
}

// Called every frame
void AGJLightBud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGJLightBud::ReturnToPlayer()
{

}

void AGJLightBud::SetFollowPoint(AActor& PointToFollow)
{
	FollowPoint = &PointToFollow;

	if (MyController)
	{
		MyController->SetBlackboardActor(FollowPoint);
	}
}

ELightBudState AGJLightBud::GetCurrentState()
{
	return CurrentState;
}

void AGJLightBud::SetCurrentState(ELightBudState StateToSet)
{
	CurrentState = StateToSet;
}


