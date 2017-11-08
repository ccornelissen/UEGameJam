// Fill out your copyright notice in the Description page of Project Settings.

#include "GJLightBud.h"
#include "GJLightBudAI.h"
#include "Components/BoxComponent.h"
#include "PowerPad.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GJPlayer.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"


// Sets default values//
AGJLightBud::AGJLightBud()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create flipbook.
	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BudSprite"));
	PaperFlipbook->SetupAttachment(RootComponent);
	PaperFlipbook->bAbsoluteRotation = true;

	MyAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	MyAudioComp->SetupAttachment(RootComponent);

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

	if (PaperFlipbook)
	{
		if (GetVelocity().Size() > 0 && WalkAnim)
		{
			PaperFlipbook->SetFlipbook(WalkAnim);

			if (GetActorRotation().Yaw > 0)
			{
				FRotator NewRot = FRotator(0, 90, 0);

				PaperFlipbook->SetRelativeRotation(NewRot);
			}
			else
			{
				FRotator NewRot = FRotator(0, -90, 0);

				PaperFlipbook->SetRelativeRotation(NewRot);
			}

		}
		else if (IdleAnim)
		{
			PaperFlipbook->SetFlipbook(IdleAnim);
		}
	}

}

void AGJLightBud::ClearFollow()
{
	if (MyController)
	{
		MyController->ClearFollowActor();

		ClearPads();
	}

	CurrentState = ELightBudState::LB_Dormant;

	if (Player)
	{
		Player->RemoveLightBud(MyNumber);
	}

	FollowPoint = nullptr;
}

void AGJLightBud::ReturnToPlayer()
{
	if (MyController)
	{
		MyController->ClearMoveToActor();

		ClearPads();
	}

	if (MovePoint)
	{
		MovePoint->Destroy();
	}

	if (MyAudioComp && ReturnSound)
	{
		MyAudioComp->SetSound(ReturnSound);

		MyAudioComp->Play();
	}

}

void AGJLightBud::SetFollowPoint(AActor& PointToFollow)
{
	FollowPoint = &PointToFollow;

	if (MyController)
	{
		MyController->SetFollowActor(FollowPoint);
	}

	ClearPads();
}

void AGJLightBud::SetMovePoint(AActor& PointToMove)
{
	MovePoint = &PointToMove;

	if (MyController)
	{
		MyController->SetMoveToActor(MovePoint);

		SetCurrentState(ELightBudState::LB_Used);
	}

	ClearPads();
}

ELightBudState AGJLightBud::GetCurrentState()
{
	return CurrentState;
}

void AGJLightBud::SetCurrentState(ELightBudState StateToSet)
{
	CurrentState = StateToSet;
}

void AGJLightBud::ClearPads()
{
	for (int32 i = 0; i < PowerPads.Num(); i++)
	{
		if (PowerPads.IsValidIndex(i))
		{
			PowerPads[i]->TurnOff();
		}
	}

	PowerPads.Reset();
}

void AGJLightBud::SetupLightTriggers()
{
	for (int32 i = 0; i < LightTriggers.Num(); i++)
	{
		if (LightTriggers.IsValidIndex(i) && LightTriggers[i])
		{
			LightTriggers[i]->OnComponentBeginOverlap.AddDynamic(this, &AGJLightBud::OnOverlapBegin);
		}
	}
}

void AGJLightBud::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && CurrentState != ELightBudState::LB_Following)
	{
		APowerPad* HitPad = Cast<APowerPad>(OtherActor);

		if (HitPad)
		{
			HitPad->TurnOn();

			PowerPads.Add(HitPad);
		}
	}
}





