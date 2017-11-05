// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPadManager.h"
#include "PowerPad.h"


// Sets default values
APowerPadManager::APowerPadManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerPadManager::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < PowerPads.Num(); i++)
	{
		if (PowerPads.IsValidIndex(i))
		{
			PowerPads[i]->SetManager(*this);
		}
			
	}
}

void APowerPadManager::PadCheck()
{
	bAllPadsEnabled = true;

	for (int32 i = 0; i < PowerPads.Num(); i++)
	{
		if (PowerPads.IsValidIndex(i))
		{
			if (PowerPads[i]->GetPadState() == EPadState::PS_Off)
			{
				bAllPadsEnabled = false;
			}
		}
	}

	if (bAllPadsEnabled == true)
	{
		ActionComplete();
	}
}

void APowerPadManager::ActionComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("Fully Powered Up"));
}


