// Fill out your copyright notice in the Description page of Project Settings.

#include "WIP.h"
#include "Bunny.h"


// Sets default values
ABunny::ABunny()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanMove = true;
}

// Called when the game starts or when spawned
void ABunny::BeginPlay()
{
	Super::BeginPlay();

	// randomly choose to start the bunny in a stopped state or a moving state
	if (FMath::FRand() > 0.5f)
	{
		PauseMovement();
	}
	else
	{
		float ChoiceTime = FMath::RandRange(MoveTimerMin, MoveTimerMax);
		GetWorld()->GetTimerManager().SetTimer(BunnyTimerHandle, this, &ABunny::StartMovement, ChoiceTime, false);
	}
}

// Called every frame
void ABunny::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanMove)
	{
		AddMovementInput(MoveDirection);
	}
}

void ABunny::StartMovement()
{
	// get a random angle in radians, and set the movement direction based on that angle
	float ChoiceAngle = FMath::RandRange(0.0f, 2.0f * PI);
	MoveDirection = FVector(FMath::Sin(ChoiceAngle), FMath::Cos(ChoiceAngle), 0);

	// get a random length of time to move, and set the pause function to execute that many seconds from now
	float ChoiceTime = FMath::RandRange(MoveTimerMin, MoveTimerMax);
	GetWorld()->GetTimerManager().SetTimer(BunnyTimerHandle, this, &ABunny::PauseMovement, ChoiceTime, false);

	// set the rotation of the character to match the movement direction
	FRotator Rot = FRotationMatrix::MakeFromX(MoveDirection).Rotator();
	SetActorRotation(Rot);
}

void ABunny::PauseMovement()
{
	// stop the movement of the character
	MoveDirection = FVector::ZeroVector;

	// get a random length of time to wait, and set the move function to execute that many seconds from now
	float ChoiceTime = FMath::RandRange(PauseTimerMin, PauseTimerMax);
	GetWorld()->GetTimerManager().SetTimer(BunnyTimerHandle, this, &ABunny::StartMovement, ChoiceTime, false);
}

void ABunny::Freeze()
{
	bCanMove = false;
}

void ABunny::Kill()
{
	// bunny death animation, etc
}

