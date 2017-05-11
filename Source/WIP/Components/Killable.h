// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Killable.generated.h"


UCLASS(Blueprintable)
class WIP_API UKillable : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKillable();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(Category="Killable", BlueprintCallable, BlueprintNativeEvent)
	void OnKill();
	
};
