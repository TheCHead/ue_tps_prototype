// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if  (PlayerController)
    {
        EndGame(false);
    }

    else
    {
        for (AShooterAIController* controller : TActorRange<AShooterAIController>(GetWorld()))
        {
            if (!controller->IsDead())
                return;
        }

        EndGame(true);
    }
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = controller->IsPlayerController() == bIsPlayerWinner;
        
        controller->GameHasEnded(controller->GetPawn(), bIsWinner);
    }

}
