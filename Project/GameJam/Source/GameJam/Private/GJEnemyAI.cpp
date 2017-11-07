// Fill out your copyright notice in the Description page of Project Settings.

#include "GJEnemyAI.h"
#include "GJLightBud.h"
#include "BehaviorTree/BlackboardComponent.h"

// Called when the game starts or when spawned
void AGJEnemyAI::BeginPlay()
{
	Super::BeginPlay();

}

void AGJEnemyAI::SetLightBud(AActor* ActorToSet)
{
	if (MyBlackBoard)
	{
		MyBlackBoard->SetValueAsObject(LightBudKeyName, ActorToSet);
	}
}

void AGJEnemyAI::SetRetreatPoint(AActor * ActorToSet)
{
	if (MyBlackBoard)
	{
		MyBlackBoard->SetValueAsObject(RetreatPointKeyName, ActorToSet);
	}
}

void AGJEnemyAI::SetStunned(bool ToSet)
{
	if (MyBlackBoard)
	{
		MyBlackBoard->SetValueAsBool(StunKeyName, ToSet);
	}
}

void AGJEnemyAI::ClearLightBud()
{
	if (MyBlackBoard)
	{
		MyBlackBoard->ClearValue(LightBudKeyName);
	}
}
