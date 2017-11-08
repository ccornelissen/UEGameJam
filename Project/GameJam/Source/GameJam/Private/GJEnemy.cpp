// Fill out your copyright notice in the Description page of Project Settings.

#include "GJEnemy.h"
#include "GJEnemyAI.h"
#include "GJLightBud.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Engine/Light.h"

// Sets default values
AGJEnemy::AGJEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BudSprite"));
	PaperFlipbook->SetupAttachment(RootComponent);
	PaperFlipbook->bAbsoluteRotation = true;
}

// Called when the game starts or when spawned
void AGJEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	MyController = Cast<AGJEnemyAI>(GetController());
}

void AGJEnemy::SetupTriggerZone()
{
	if (TriggerZone)
	{
		TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AGJEnemy::OnOverlapBegin);
	}
}

void AGJEnemy::Stun(float StunForce)
{
	CurrentState = EEnemyState::ES_Stunned;

	FVector NewVector = GetActorLocation() - (GetActorForwardVector() * StunForce);

	SetActorLocation(NewVector);

	if (MyController)
	{
		MyController->SetStunned(true);

		MyController->ClearLightBud();
	}

	GetWorld()->GetTimerManager().SetTimer(StunHandle, this, &AGJEnemy::RangeCheck, fStunTimer, false);
}

void AGJEnemy::Retreat()
{
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;

	if (MyController && RetreatLocation)
	{
		MyController->SetRetreatPoint(RetreatLocation);
	}

	CurrentState = EEnemyState::ES_Retreating;
}

void AGJEnemy::RangeCheck()
{
	if (LightBud)
	{
		float DistTo;

		DistTo = FVector::Dist(GetActorLocation(), LightBud->GetActorLocation());

		if (DistTo < fPersueDistance && MyController)
		{
			MyController->SetLightBud(LightBud);

			CurrentState = EEnemyState::ES_Chasing;
		}
		else
		{
			LightBud = nullptr;

			CurrentState = EEnemyState::ES_Dormant;
		}
	}

	if (MyController)
	{
		MyController->SetStunned(false);
	}
}

void AGJEnemy::Attack()
{
	if (LightBud && PortLocation)
	{
		if (DeathLight)
		{
			GetWorld()->SpawnActor<ALight>(DeathLight, LightBud->GetActorLocation(), LightBud->GetActorRotation());
		}

		LightBud->ReturnToPlayer();
		LightBud->ClearFollow();

		LightBud->SetActorLocation(PortLocation->GetActorLocation());

		LightBud = nullptr;

		MyController->ClearLightBud();

		CurrentState = EEnemyState::ES_Dormant;
	}
}

void AGJEnemy::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (LightBud == nullptr)
	{
		LightBud = Cast<AGJLightBud>(OtherActor);
	}
	
	if (LightBud && MyController && CurrentState == EEnemyState::ES_Dormant)
	{
		MyController->SetLightBud(LightBud);

		CurrentState = EEnemyState::ES_Chasing;
	}
}

// Called every frame
void AGJEnemy::Tick(float DeltaTime)
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

		if (LightBud && CurrentState != EEnemyState::ES_Stunned)
		{
			float Dist = FVector::Dist(GetActorLocation(), LightBud->GetActorLocation());

			if(Dist < fAttackRange)
			{
				PaperFlipbook->SetFlipbook(AttackAnim);
				Attack();
			}
		}
	}

	if (CurrentState == EEnemyState::ES_Chasing)
	{
		RangeCheck();
	}
	

}