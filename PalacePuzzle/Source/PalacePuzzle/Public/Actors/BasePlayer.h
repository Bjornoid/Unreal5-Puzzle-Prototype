// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PALACEPUZZLE_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABasePlayer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	APlayerController* PlayerController;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UInputMappingContext* PlayerMappingContext;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UInputAction* MoveForwardAction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UInputAction* MoveRightAction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UInputAction* TurnToAction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UInputAction* LookUpAction;
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(const struct FInputActionValue& ActionValue);
	void MoveRight(const struct FInputActionValue& ActionValue);
	void TurnTo(const struct FInputActionValue& ActionValue);
	void LookUp(const struct FInputActionValue& ActionValue);
	float MoveScale;
};
