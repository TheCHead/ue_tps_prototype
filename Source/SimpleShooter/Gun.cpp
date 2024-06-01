// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

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
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	
	FHitResult HitResult;
	FVector ShotDirection;

	//DrawDebugCamera(GetWorld(), viewpointLocation, viewpointRotation, 90, 2, FColor::Red, true);
	if	(GunTrace(HitResult, ShotDirection))
	{
		//DrawDebugPoint(GetWorld(), hit.ImpactPoint, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, HitResult.ImpactPoint, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, HitResult.ImpactPoint);
		

		AActor* hitActor = HitResult.GetActor();

		if	(hitActor)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController* PawnController = GetOwnerController();
			if	(!PawnController)
				return;
			hitActor->TakeDamage(Damage, DamageEvent, PawnController, this);
		}
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

bool AGun::GunTrace(FHitResult &Hit, FVector &ShotDirection)
{
	AController* PawnController = GetOwnerController();

	if	(!PawnController)
		return false;
	
	FVector viewpointLocation;
	FRotator viewpointRotation;

	PawnController->GetPlayerViewPoint(viewpointLocation, viewpointRotation);

	ShotDirection = -viewpointRotation.Vector();

	FVector traceEnd = viewpointLocation + viewpointRotation.Vector() * 1000.0;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	Params.AddIgnoredActor(this);
	return GetWorld()->LineTraceSingleByChannel(Hit, viewpointLocation, traceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController *AGun::GetOwnerController() const
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());

    if	(!OwnerPawn) 
		return nullptr;

	return OwnerPawn->GetController();
}
