// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstancePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PALACEPUZZLE_API UAnimInstancePlayer : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	float Velocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	float Direction;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PreviewWindowUpdate();
	virtual void PreviewWindowUpdate_Implementation();

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
