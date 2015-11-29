// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Interfaces/PowerupInterface.h"
#include "EvaGameState.generated.h"

/**
 * 
 */
UCLASS()
class EVALUATION2_API AEvaGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AActor*> Powerups; // acculy iz IPowerupInterface*

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AActor*> Waypoints; // acculy iz IWaypointInterface*

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AActor*> Spawnpoints; // TODO: what exactly is a spawnpoint?!

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AActor*> Walls; // acculy iz IWallInterface*
	
};
