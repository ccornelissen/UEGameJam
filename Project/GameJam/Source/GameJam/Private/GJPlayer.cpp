// Fill out your copyright notice in the Description page of Project Settings.

#include "GJPlayer.h"
#include "Camera/CameraComponent.h"
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

// Sets default values
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
}

// Called when the game starts or when spawned
void AGJPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	MyController = Cast<APlayerController>(GetController());

	if (MyController)
	{
		MyController->bShowMouseCursor = true;
	}
}

// Called every frame
void AGJPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGJPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGJPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGJPlayer::MoveRight);
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &AGJPlayer::ThrowBud);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AGJPlayer::AimBud);
	PlayerInputComponent->BindAction("Recall", IE_Pressed, this, &AGJPlayer::RecallBuds);
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

void AGJPlayer::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AGJLightBud* LightBud = Cast<AGJLightBud>(OtherActor);

	if (LightBud)
	{
		if (LightBud->GetCurrentState() == ELightBudState::LB_Dormant)
		{
			LightBuds.Add(LightBud);

			LightBud->SetCurrentState(ELightBudState::LB_Following);

			if (LightBuds.Num() == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Follwing Player"));

				LightBud->SetFollowPoint(*this);
			}
			else if(LightBuds.IsValidIndex(LightBuds.Num() - 2))
			{
				UE_LOG(LogTemp, Warning, TEXT("Follwing Light Bud!"));

				LightBud->SetFollowPoint(*LightBuds[LightBuds.Num() - 2]);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Ruh ro Invalid light bud some how. Panic. Panic now."))
			}
		}
	}
}

void AGJPlayer::AimBud()
{
	if (MyController)
	{
		float fMouseX;
		float fMouseY;

		MyController->GetMousePosition(fMouseX, fMouseY);

		if (AimingActor && ThrowPoint)
		{
			AGJAimActor* CurActor = GetWorld()->SpawnActor<AGJAimActor>(AimingActor, ThrowPoint->GetComponentLocation(), GetActorRotation());

			if (CurActor->GetSphereComp())
			{
				UE_LOG(LogTemp, Warning, TEXT("Mouse X: %f, Mouse Y: %f"), fMouseX, fMouseY);

				FVector ThrowVector = FVector(fMouseX, fMouseY, 0);

				CurActor->GetSphereComp()->AddImpulse(ThrowVector * fThrowForce);
			}
		}

	}
}

void AGJPlayer::ThrowBud()
{
}

void AGJPlayer::RecallBuds()
{
}

void AGJPlayer::MoveForward(float Value)
{
	const FVector Direction = -GetActorRightVector();

	AddMovementInput(Direction, Value);
}

void AGJPlayer::MoveRight(float Value)
{
	const FVector Direction = GetActorForwardVector();

	if (Value > 0 && WalkRight)
	{
		PaperFlipbook->SetFlipbook(WalkRight);
	}
	else if (Value < 0 && WalkLeft)
	{
		PaperFlipbook->SetFlipbook(WalkLeft);
	}
	else if (Idle)
	{
		PaperFlipbook->SetFlipbook(Idle);
	}

	AddMovementInput(Direction, Value);
}