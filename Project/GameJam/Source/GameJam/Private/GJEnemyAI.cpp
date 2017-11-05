// Fill out your copyright notice in the Description page of Project Settings.

#include "GJEnemyAI.h"
#include "GJLightBud.h"
#include "BehaviorTree/BlackboardComponent.h"

void AGJEnemyAI::SetLightBud(AActor* ActorToSet)
{
	if (MyBlackBoard)
	{
		MyBlackBoard->SetValueAsObject(LightBudKeyName, ActorToSet);
	}
}

void AGJEnemyAI::ClearLightBud()
{
	if (MyBlackBoard)
	{
		MyBlackBoard->ClearValue(LightBudKeyName);
	}
}
