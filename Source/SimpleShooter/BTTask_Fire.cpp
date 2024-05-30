// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fire.h"
#include "ShooterCharacter.h"
#include "AIController.h"

UBTTask_Fire::UBTTask_Fire()
{
    NodeName = TEXT("Fire");
}

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if  (!OwnerComp.GetAIOwner())
        return EBTNodeResult::Failed;

    AShooterCharacter* shooterChar = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if  (!shooterChar)
        return EBTNodeResult::Failed;

    shooterChar->Fire();

    return EBTNodeResult::Succeeded;
}