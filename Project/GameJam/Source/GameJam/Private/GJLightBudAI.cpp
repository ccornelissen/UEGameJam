// Fill out your copyright notice in the Description page of Project Settings.

#include "GJLightBudAI.h"
#include "BehaviorTree/BlackboardComponent.h"

void AGJLightBudAI::BeginPlay()
{
	Super::BeginPlay();
}

void AGJLightBudAI::SetBlackboardActor(AActor* ActorToSet)
{
	if (MyBlackBoard)
	{
		MyBlackBoard->SetValueAsObject(FollowKeyName, ActorToSet);
	}

}