// Fill out your copyright notice in the Description page of Project Settings.

#include "GJAimActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AGJAimActor::AGJAimActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereCollider);
	SphereCollider->SetSimulatePhysics(false);
}

USphereComponent * AGJAimActor::GetSphereComp()
{
	return SphereCollider;
}

// Called when the game starts or when spawned
void AGJAimActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGJAimActor::DestroyAimActor()
{
	Destroy();
}


