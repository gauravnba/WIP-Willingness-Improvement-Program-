// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class WIP_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
	// moves the player along the x axis (the player's local forward / back axis)
	void MoveXAxis(float Val);
	
	UFUNCTION()
	// moves the player along the y axis (the player's local right / left axis)
	void MoveYAxis(float Val);

	UFUNCTION()
	// rotation around the z axis (yaw, or looking left / right)
	void RotateZAxis(float Val);

	UFUNCTION()
	// rotation around the y axis (pitch, or looking up / down)
	void RotateYAxis(float Val);

	UFUNCTION()
	// the player calls the OnInteract function on an actor within the player's look direction and interaction range
	void Interact();

	UFUNCTION(BlueprintCallable, Category="PlayerCharacter")
	void Freeze();

	UFUNCTION(BlueprintCallable, Category="PlayerCharacter")
	// the player uses this to escape from the game. only called when the narrator freezes the game
	void Escape();

	UFUNCTION(BlueprintImplementableEvent)
	// the player attacks. only called when the sword is equipped.
	void OnAttack();

	UPROPERTY(EditAnywhere)
	// the range that the player can interact with object triggers in the world
	float InteractRange;

	UPROPERTY(BlueprintReadWrite)
	// whether the player has the sword equipped
	bool bWeaponEquipped;

	UPROPERTY(BlueprintReadWrite)
	// whether the player has killed a bunny
	bool bHasKilledBunny;

	// whether the player can move and rotate
	UPROPERTY(BlueprintReadOnly)
	bool bCanMove;
};
