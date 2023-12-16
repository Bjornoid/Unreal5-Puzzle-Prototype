// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AnimInstancePlayer.h"


void UAnimInstancePlayer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		Velocity = Pawn->GetVelocity().Size();
		Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
	}
	else
	{
		// NUll
		PreviewWindowUpdate_Implementation();
	}
}

void UAnimInstancePlayer::PreviewWindowUpdate_Implementation()
{

}
