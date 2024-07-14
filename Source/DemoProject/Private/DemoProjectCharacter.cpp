// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoProjectCharacter.h"

#include "AbilitySystemComponent.h"
#include "DemoPlayerState.h"
#include "DemoProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADemoProjectCharacter

ADemoProjectCharacter::ADemoProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void ADemoProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	InitAbilitySystemComponent();
}

void ADemoProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADemoProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADemoProjectCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void ADemoProjectCharacter::InitAbilitySystemComponent()
{
	if (ADemoPlayerState* DemoPlayerState = GetPlayerState<ADemoPlayerState>();
		ensureMsgf(DemoPlayerState,
		           TEXT("\"%s\": Expected currently used PlayerState to be a subclass of DemoPlayerState"),
		           *GetNameSafe(this)))
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
			IsValid(AbilitySystemComponent))
		{
			AbilitySystemComponent->InitAbilityActorInfo(DemoPlayerState, this);
			DemoPlayerState->InitAbilitySystemComponent();
		}
	}
}

UAbilitySystemComponent* ADemoProjectCharacter::GetAbilitySystemComponent() const
{
	if (const IAbilitySystemInterface* PlayerStateWithAbilities = Cast<IAbilitySystemInterface>(GetPlayerState());
		ensureMsgf(PlayerStateWithAbilities,
		           TEXT("\"%s\": Expected PlayerState instance that implements IAbilitySystemInterface"),
		           *GetNameSafe(this)))
	{
		return PlayerStateWithAbilities->GetAbilitySystemComponent();
	}
	return nullptr;
}


void ADemoProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ADemoProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
