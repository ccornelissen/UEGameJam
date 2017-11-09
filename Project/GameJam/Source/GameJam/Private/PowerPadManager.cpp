// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPadManager.h"
#include "PowerPad.h"
#include "Engine/Light.h"
#include "Components/AudioComponent.h"
#include "GJEnemy.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"


// Sets default values
APowerPadManager::APowerPadManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	MyAudioComp->SetupAttachment(RootComponent);
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

	if (bHasLightsToTurnOn)
	{
		for (int32 i = 0; i < LightsToTurnOn.Num(); i++)
		{
			if (LightsToTurnOn.IsValidIndex(i))
			{
				LightsToTurnOn[i]->SetEnabled(false);
			}
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
	if (bHasDoorToOpen)
	{
		if (DoorToMove && NewDoorLocation)
		{
			DoorToMove->SetActorLocation(NewDoorLocation->GetActorLocation());
		}
	}

	if (bHasLightsToTurnOn)
	{
		for (int32 i = 0; i < LightsToTurnOn.Num(); i++)
		{
			if (LightsToTurnOn.IsValidIndex(i))
			{
				LightsToTurnOn[i]->SetEnabled(true);
			}
		}
	}

	if (bHasEnemyToScare)
	{
		for (int32 i = 0; i < EnemiesToScare.Num(); i++)
		{
			if (EnemiesToScare.IsValidIndex(i))
			{
				EnemiesToScare[i]->Retreat();
			}
		}
	}

	if (bHasSequenceToPlay && SequenceToPlay)
	{
		ULevelSequencePlayer* CinePlayer = SequenceToPlay->SequencePlayer;

		if (CinePlayer)
		{
			CinePlayer->Play();
		}
	}

	MyAudioComp->Play();
}


