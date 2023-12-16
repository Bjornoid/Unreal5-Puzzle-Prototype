// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "../../PalacePuzzle.h"

ABasePlayer::ABasePlayer() : MoveScale(1.f)
{
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(35.f, 0.f, 77.f));
	Camera->bUsePawnControlRotation = true;
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerMappingContext = NewObject<UInputMappingContext>(this);

	//Set Input Actions
	MoveForwardAction = NewObject<UInputAction>(this);
	MoveForwardAction->ValueType = EInputActionValueType::Axis1D;
	PlayerMappingContext->MapKey(MoveForwardAction, EKeys::W);
	FEnhancedActionKeyMapping& SMapping = PlayerMappingContext->MapKey(MoveForwardAction, EKeys::S);
	UInputModifierNegate* SNegate = NewObject<UInputModifierNegate>(this);
	SMapping.Modifiers.Add(SNegate);
	MoveRightAction = NewObject<UInputAction>(this);
	MoveRightAction->ValueType = EInputActionValueType::Axis1D;
	PlayerMappingContext->MapKey(MoveRightAction, EKeys::D);
	FEnhancedActionKeyMapping& AMapping = PlayerMappingContext->MapKey(MoveRightAction, EKeys::A);
	UInputModifierNegate* ANegate = NewObject<UInputModifierNegate>(this);
	AMapping.Modifiers.Add(ANegate);
	TurnToAction = NewObject<UInputAction>(this);
	TurnToAction->ValueType = EInputActionValueType::Axis1D;
	PlayerMappingContext->MapKey(TurnToAction, EKeys::MouseX);
	LookUpAction = NewObject<UInputAction>(this);
	LookUpAction->ValueType = EInputActionValueType::Axis1D;
	FEnhancedActionKeyMapping& YMapping = PlayerMappingContext->MapKey(LookUpAction, EKeys::MouseY);
	UInputModifierNegate* YNegate = NewObject<UInputModifierNegate>(this);
	YMapping.Modifiers.Add(YNegate);

	//Bind Mapping Context
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	PlayerController = Cast<APlayerController>(GetController());
	if (EIC && PlayerController)
	{
		EIC->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ABasePlayer::MoveForward);
		EIC->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ABasePlayer::MoveRight);
		EIC->BindAction(TurnToAction, ETriggerEvent::Triggered, this, &ABasePlayer::TurnTo);
		EIC->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &ABasePlayer::LookUp);

		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (Subsystem)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void ABasePlayer::MoveForward(const FInputActionValue& ActionValue)
{
	float Input = ActionValue.Get<FInputActionValue::Axis1D>();


	AddMovementInput(FRotator(0.f, GetControlRotation().Yaw, 0.f).Vector(), Input);
}

void ABasePlayer::MoveRight(const FInputActionValue& ActionValue)
{
	float Input = ActionValue.Get<FInputActionValue::Axis1D>();

	AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetScaledAxis(EAxis::Y), Input);
}

void ABasePlayer::TurnTo(const FInputActionValue& ActionValue)
{
	float Input = ActionValue.Get<FInputActionValue::Axis1D>();

	AddControllerYawInput(Input);
}

void ABasePlayer::LookUp(const FInputActionValue& ActionValue)
{
	float Input = ActionValue.Get<FInputActionValue::Axis1D>();

	AddControllerPitchInput(Input);
}
