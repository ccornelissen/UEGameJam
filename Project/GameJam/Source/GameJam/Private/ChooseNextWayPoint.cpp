// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "GJEnemy.h"
#include "GJEnemyAI.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//Get the blackboard component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	//Get the current waypoint the AI is on 
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	//Get a reference to the controlled monster pawn
	AGJEnemy* MyEnemy = Cast<AGJEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (!ensure(MyEnemy))
	{
		return EBTNodeResult::Failed;
	}

	if (MyEnemy->PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy patrol points are not set on the spawner!"));
	}

	if (Index > MyEnemy->PatrolPoints.Num() - 1)
	{
		Index = 0;
	}

	if (MyEnemy->PatrolPoints[Index] != nullptr)
	{
		BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, MyEnemy->PatrolPoints[Index]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy patrol has an empty array element, check the spawner!"));
		return EBTNodeResult::Failed;
	}

	int32 NextPoint = Index + 1;


	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextPoint);

	return EBTNodeResult::Succeeded;
}
