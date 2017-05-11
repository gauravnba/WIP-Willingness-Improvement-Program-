// Fill out your copyright notice in the Description page of Project Settings.

#include "WIP.h"
#include "PlayerCharacter.h"
#include "../Components/Interactable.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bWeaponEquipped = false;
	bCanMove = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);

	Input->BindAxis("MoveXAxis", this, &APlayerCharacter::MoveXAxis);
	Input->BindAxis("MoveYAxis", this, &APlayerCharacter::MoveYAxis);

	Input->BindAxis("RotateZAxis", this, &APlayerCharacter::RotateZAxis);
	Input->BindAxis("RotateYAxis", this, &APlayerCharacter::RotateYAxis);

	// interact
	Input->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	Input->BindAction("Escape", IE_Pressed, this, &APlayerCharacter::Escape);
	Input->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::OnAttack);
}

void APlayerCharacter::MoveXAxis(float Val)
{
	if (bCanMove && (Controller != NULL) && (Val != 0.0f))
	{
		// get the forward vector of the player's look direction
		FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		// move along the forward vector depending on the input
		AddMovementInput(Direction, Val);
	}
}

void APlayerCharacter::MoveYAxis(float Val)
{
	if (bCanMove && (Controller != NULL) && (Val != 0.0f))
	{
		// get the right vector of the player's look direction
		FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		// move along the right vector depending on the input
		AddMovementInput(Direction, Val);
	}
}

void APlayerCharacter::RotateZAxis(float Val)
{
	if (bCanMove)
	{
		AddControllerYawInput(Val);
	}
}

void APlayerCharacter::RotateYAxis(float Val)
{
	if (bCanMove)
	{
		AddControllerPitchInput(Val);
	}
}

void APlayerCharacter::Interact()
{
	if (Controller == NULL)
	{
		return;
	}

	// get camera location and rotation
	FVector PlayerViewLoc;
	FRotator PlayerViewRot;
	Controller->GetPlayerViewPoint(PlayerViewLoc, PlayerViewRot);

	// raycast with actors in the scene
	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, PlayerViewLoc, PlayerViewLoc + PlayerViewRot.Vector() * InteractRange, ECollisionChannel::ECC_Visibility);

	// if the ray hit and the hit actor has a interactable component, call OnInteract
	if (bHit)
	{
		UInteractable* interactable = Hit.Actor->FindComponentByClass<UInteractable>();
		if (interactable != NULL)
		{
			interactable->OnPlayerInteract();
		}
	}
}

void APlayerCharacter::Freeze()
{
	bCanMove = false;
}

void APlayerCharacter::Escape()
{
	bCanMove = true;
}

