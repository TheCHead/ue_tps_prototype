// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay(); 

    if  (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        APawn* AIPawn = GetPawn();
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), AIPawn->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    // MoveToActor(PlayerPawn, 200.f);

    // if (LineOfSightTo(PlayerPawn))
    // {
    //     SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
    //     MoveToActor(PlayerPawn, AcceptanceRadius);
    // }

    // else
    // {
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    // }

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (LineOfSightTo(PlayerPawn))
    {
        FVector PlayerLocation = PlayerPawn->GetActorLocation();
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerLocation);
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerLocation);
    }

    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
}
