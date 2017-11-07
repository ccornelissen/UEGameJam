// Fill out your copyright notice in the Description page of Project Settings.

#include "GJPlayer.h"
#include "GJPlayerController.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GJLightBud.h"
#include "GJAimActor.h"
#include "GJEnemy.h"
#include "GJUserWidget.h"

// Sets default values//
AGJPlayer::AGJPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Create Camera Arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = false;

	//Create Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	//Create flipbook.
	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerSprite"));
	PaperFlipbook->SetupAttachment(RootComponent);
	PaperFlipbook->bAbsoluteRotation = true;
}

void AGJPlayer::SetTutorial(FText InText, float fTimer)
{
	if (MyWidget)
	{
		MyWidget->SetTutorialText(InText, fTimer);
	}
}

// Called when the game starts or when spawned
void AGJPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	MyController = Cast<AGJPlayerController>(GetController());

	if (MyController)
	{
		MyController->bShowMouseCursor = true;

		MyWidget = &MyController->GetUserWidget();
	}
}

void AGJPlayer::ResetAnim()
{
	bAnimSwitch = true;
}

// Called every frame
void AGJPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAiming)
	{
		AimBud();
	}

	if (PaperFlipbook && bAnimSwitch == true)
	{
		if (GetVelocity().Size() > 0 && WalkAnim)
		{
			PaperFlipbook->SetFlipbook(WalkAnim);

		}
		else if (IdleAnim)
		{
			PaperFlipbook->SetFlipbook(IdleAnim);
		}
	}

}

// Called to bind functionality to input
void AGJPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGJPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGJPlayer::MoveRight);
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &AGJPlayer::OrderBud);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AGJPlayer::StartAiming);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AGJPlayer::StopAiming);
	PlayerInputComponent->BindAction("Recall", IE_Pressed, this, &AGJPlayer::RecallBuds);
	PlayerInputComponent->BindAction("Kick", IE_Pressed, this, &AGJPlayer::Kick);
}

void AGJPlayer::SetCollectionBox(UBoxComponent* BoxToSet)
{
	if (BoxToSet)
	{
		CollectionBox = BoxToSet;
	}

	if (CollectionBox)
	{
		CollectionBox->OnComponentBeginOverlap.AddDynamic(this, &AGJPlayer::OnOverlapBegin);
		CollectionBox->bGenerateOverlapEvents = true;
	}
}

void AGJPlayer::SetKickBox(UBoxComponent * BoxToSet)
{
	if (BoxToSet)
	{
		KickBox = BoxToSet;
	}

	if (KickBox)
	{
		KickBox->OnComponentBeginOverlap.AddDynamic(this, &AGJPlayer::OnOverlapBegin);
		KickBox->bGenerateOverlapEvents = false;
	}
}

void AGJPlayer::StartAiming()
{
	if (AimActor == nullptr)
	{
		AimActor = GetWorld()->SpawnActor<AGJAimActor>(AimingActor, GetActorLocation(), GetActorRotation());
	}

	bAiming = true;
}

void AGJPlayer::StopAiming()
{
	bAiming = false;

	if (AimActor)
	{
		AimActor->DestroyAimActor();

		AimActor = nullptr;
	}
}

void AGJPlayer::AimBud()
{
	if (MyController && bAiming && AimActor)
	{
		FHitResult HitPos;

		if (MyController->GetHitResultUnderCursor(ECC_Visibility, true, HitPos))
		{
			AimActor->SetActorLocation(HitPos.Location);
		}
	}
}

void AGJPlayer::OrderBud()
{
	FHitResult HitPos;

	if (MyController && LightBuds.Num() > 0)
	{
		if (MoveToActor && MyController->GetHitResultUnderCursor(ECC_Visibility, true, HitPos))
		{
			AGJAimActor* SpawnedActor  = GetWorld()->SpawnActor<AGJAimActor>(MoveToActor, HitPos.Location, GetActorRotation());

			if (LightBuds.IsValidIndex(iCurrentBud))
			{
				LightBuds[iCurrentBud]->SetMovePoint(*SpawnedActor);

				LightBuds.RemoveAt(iCurrentBud);

				RearrangeBuds();
			}

			if (PointAnim)
			{
				bAnimSwitch = false;

				PaperFlipbook->SetFlipbook(PointAnim);

				GetWorld()->GetTimerManager().SetTimer(AnimHandle, this, &AGJPlayer::ResetAnim, fAnimTimer);
				
			}
		}
	}
}

void AGJPlayer::RecallBuds()
{
	for (TActorIterator<AGJLightBud> BudItr(GetWorld()); BudItr; ++BudItr)
	{
		AGJLightBud* CurBud = *BudItr;

		if (CurBud)
		{
			if (CurBud->GetCurrentState() == ELightBudState::LB_Used)
			{
				CurBud->ReturnToPlayer();

				LightBuds.Add(CurBud);

				CurBud->SetCurrentState(ELightBudState::LB_Following);

				SetBudFollow(*CurBud);
			}
		}

		if (PointAnim)
		{
			bAnimSwitch = false;

			PaperFlipbook->SetFlipbook(PointAnim);

			GetWorld()->GetTimerManager().SetTimer(AnimHandle, this, &AGJPlayer::ResetAnim, fAnimTimer);
		}

	}

}

void AGJPlayer::RemoveLightBud(int32 iNum)
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), LightBuds.Num());

	LightBuds.RemoveAt(iNum);

	UE_LOG(LogTemp, Warning, TEXT("%d"), LightBuds.Num());

	RearrangeBuds();
}

void AGJPlayer::RearrangeBuds()
{
	for (int32 i = 0; i < LightBuds.Num(); i++)
	{
		if (LightBuds.IsValidIndex(i))
		{
			if (i == 0)
			{
				LightBuds[i]->SetFollowPoint(*this);

				UE_LOG(LogTemp, Warning, TEXT("Player"));

				LightBuds[i]->MyNumber = i;
			}
			else
			{
				LightBuds[i]->SetFollowPoint(*LightBuds[i - 1]);

				UE_LOG(LogTemp, Warning, TEXT("Light Bud"));

				LightBuds[i]->MyNumber = i;
			}
		}
	}
}

void AGJPlayer::SetBudFollow(AGJLightBud& CurBud)
{
	AGJLightBud* TempBud = &CurBud;
	if (TempBud)
	{
		if (LightBuds.Num() == 1)
		{
			TempBud->SetFollowPoint(*this);
		}
		else if (LightBuds.IsValidIndex(LightBuds.Num() - 2))
		{

			TempBud->SetFollowPoint(*LightBuds[LightBuds.Num() - 2]);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Ruh ro Invalid light bud some how. Panic. Panic now."))
		}
	}
}

void AGJPlayer::Kick()
{
	if (bCanKick)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can Kick"));

		bCanKick = false;

		bKicking = true;

		if (KickAnim)
		{
			bAnimSwitch = false;

			PaperFlipbook->SetFlipbook(KickAnim);

			GetWorld()->GetTimerManager().SetTimer(AnimHandle, this, &AGJPlayer::ResetAnim, fAnimTimer);
		}

		if (CollectionBox && KickBox)
		{
			CollectionBox->bGenerateOverlapEvents = false;

			KickBox->bGenerateOverlapEvents = true;
		}

		GetWorld()->GetTimerManager().SetTimer(KickHandle, this, &AGJPlayer::ResetKick, fKickTimer, false);
	}
}

void AGJPlayer::ResetKick()
{
	bCanKick = true;

	if (CollectionBox && KickBox)
	{
		CollectionBox->bGenerateOverlapEvents = true;

		KickBox->bGenerateOverlapEvents = false;
	}

	bKicking = false;
}

void AGJPlayer::MoveForward(float Value)
{
	const FVector Direction = -GetActorRightVector();

	AddMovementInput(Direction, Value);
}

void AGJPlayer::MoveRight(float Value)
{
	const FVector Direction = GetActorForwardVector();

	if (Value > 0)
	{
		FRotator NewRot = FRotator(0, 0, 0);

		PaperFlipbook->SetRelativeRotation(NewRot);
	}
	else if (Value < 0)
	{
		FRotator NewRot = FRotator(0, 180, 0);

		PaperFlipbook->SetRelativeRotation(NewRot);
	}

	AddMovementInput(Direction, Value);
}

void AGJPlayer::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AGJLightBud* LightBud = Cast<AGJLightBud>(OtherActor);

	if (LightBud)
	{
		if (LightBud->GetCurrentState() == ELightBudState::LB_Dormant)
		{
			LightBud->Player = this;

			LightBuds.Add(LightBud);

			LightBud->MyNumber = LightBuds.Num() - 1;

			LightBud->SetCurrentState(ELightBudState::LB_Following);

			SetBudFollow(*LightBud);
		}
	}

	AGJEnemy* Enemy = Cast<AGJEnemy>(OtherActor);

	if (Enemy && bKicking)
	{
		UE_LOG(LogTemp, Warning, TEXT("Kicking"));

		Enemy->Stun(fKickDistance);
	}
}