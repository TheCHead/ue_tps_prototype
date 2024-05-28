// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if	(!OwnerPawn) 
		return;

	AController* PawnController = OwnerPawn->GetController();

	if	 (!PawnController)
		return;
	
	FVector viewpointLocation;
	FRotator viewpointRotation;

	PawnController->GetPlayerViewPoint(viewpointLocation, viewpointRotation);

	FVector traceEnd = viewpointLocation + viewpointRotation.Vector() * 1000.0;

	FHitResult hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(hit, viewpointLocation, traceEnd, ECollisionChannel::ECC_GameTraceChannel1);

	//DrawDebugCamera(GetWorld(), viewpointLocation, viewpointRotation, 90, 2, FColor::Red, true);
	if	(bHit)
	{
		FVector shotDir = -viewpointRotation.Vector();
		//DrawDebugPoint(GetWorld(), hit.ImpactPoint, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, hit.ImpactPoint, shotDir.Rotation());
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

