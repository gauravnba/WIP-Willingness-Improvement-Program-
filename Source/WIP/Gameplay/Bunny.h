// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Bunny.generated.h"

UCLASS()
class WIP_API ABunny : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABunny();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	// Sets the movement direction, starts movement, and waits to pause movement
	void StartMovement();

	UFUNCTION()
	// Stops movement and waits to start movement again
	void PauseMovement();

	UFUNCTION()
	// Stops the bunny from moving
	void Freeze();

	UFUNCTION()
	// Kills the bunny
	void Kill();

	UPROPERTY(EditAnywhere)
	// Minimum length of time while moving
	float MoveTimerMin;

	UPROPERTY(EditAnywhere)
	// Maximum length of time while moving
	float MoveTimerMax;

	UPROPERTY(EditAnywhere)
	// Minimum length of time while stopped
	float PauseTimerMin;

	UPROPERTY(EditAnywhere)
	// Maximum length of time while stopped
	float PauseTimerMax;

private:
	// whether the bunny is capable of moving
	bool bCanMove;

	// Current movement direction
	FVector MoveDirection;

	// Manages the movement and pausing timers
	FTimerHandle BunnyTimerHandle;
};
