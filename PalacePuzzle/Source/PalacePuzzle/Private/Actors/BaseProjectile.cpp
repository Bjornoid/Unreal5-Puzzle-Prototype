// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseProjectile.h"
#include "NavAreas/NavArea.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseProjectile::ABaseProjectile() : DestroyTime(3.f), Scale(.15f, .15f, .15f), BaseDamage(1.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision"); SetRootComponent(Collision);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::HandleOverlap);
	Collision->SetWorldScale3D(Scale);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Collision);
	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetRelativeScale3D(FVector(.6f, .6f, .6f));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseProjectile::K2_DestroyActor, DestroyTime, false);

	// need to be in begin play to get this because it is set through BP
	Collision->AreaClass = CollisionAreaClass;
}

void ABaseProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


