// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseGun.h"
#include "../../PalacePuzzle.h"

// Sets default values
ABaseGun::ABaseGun() : Alive(true), BaseDelay(.2f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMesh);
}

// Called when the game starts or when spawned
void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
	

	AActor* parentActor = GetParentActor();
	if (parentActor)
	{
		ParentPawn = Cast<APawn>(parentActor);
	}
	else
	{
		UE_LOG(Game, Error, TEXT("We need to be owned by a pawn"));
		Destroy();
	}
}

void ABaseGun::Attack()
{
	if (CanAttack())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = ParentPawn;
		SpawnParams.Owner = this;

		AActor* ProjectileSpawned = GetWorld()->SpawnActor<AActor>(ProjectileClass, SkeletalMesh->GetSocketLocation(SpawnSocketName), ParentPawn->GetBaseAimRotation(), SpawnParams);

		if (!ProjectileSpawned)
		{
			UE_LOG(Game, Warning, TEXT("Projectile was not spawned"));
		}

		DelayActive = true;

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseGun::StopActive, BaseDelay, false);
	}
}

bool ABaseGun::CanAttack() const
{
	return (!DelayActive && Alive);
}

void ABaseGun::StopActive()
{
	DelayActive = false;
}

void ABaseGun::OwnerDied(float NotUsed)
{
	Alive = false;
}



