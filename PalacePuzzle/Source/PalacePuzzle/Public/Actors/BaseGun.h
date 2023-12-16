// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

UCLASS()
class PALACEPUZZLE_API ABaseGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	APawn* ParentPawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FName SpawnSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool DelayActive;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool Alive;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float BaseDelay;

public:	
	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	bool CanAttack() const;

	UFUNCTION(BlueprintCallable)
	void StopActive();

	UFUNCTION(BlueprintCallable)
	void OwnerDied(float NotUsed);

};
