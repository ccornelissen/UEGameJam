// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPad.h"
#include "PowerPadManager.h"

// Sets default values
APowerPad::APowerPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerPad::BeginPlay()
{
	Super::BeginPlay();

	MyMesh = FindComponentByClass<UStaticMeshComponent>();
}

EPadState APowerPad::GetPadState()
{
	return CurrentPadState;
}

void APowerPad::SetPadState(EPadState StateToSet)
{
	CurrentPadState = StateToSet;
}

void APowerPad::SetManager(APowerPadManager & ManagerToSet)
{
	MyManager = &ManagerToSet;
}

void APowerPad::TurnOn()
{
	SetPadState(EPadState::PS_On);

	if (MyManager)
	{
		MyManager->PadCheck();
	}

	if (MyMesh && OnMat)
	{
		MyMesh->SetMaterial(0, OnMat);
	}
}

void APowerPad::TurnOff()
{
	SetPadState(EPadState::PS_Off);

	if (MyMesh && OffMat)
	{
		MyMesh->SetMaterial(0, OffMat);
	}
}


