// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PALACEPUZZLE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UChildActorComponent* ChildActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<AActor> WeaponClass;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UAnimInstanceIronSights* AnimInstance;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class ABaseIronSights* CurrentWeapon;*/

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
