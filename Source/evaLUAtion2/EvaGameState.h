// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Interfaces/PowerupInterface.h"
#include "EvaCharacter.h"
#include <lauxlib.h>
#include <luabind/error.hpp>
#include <map>
#include "Dict.h"
#include "EvaGameState.generated.h"

/**
 * 
 */
UCLASS()
class EVALUATION2_API AEvaGameState : public AGameState
{
	GENERATED_BODY()

	std::map<int32, lua_State*> TeamLuaContexts;
	
public:

	AEvaGameState(const FObjectInitializer &PCIP);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AActor*> Powerups; // acculy iz IPowerupInterface*

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AActor*> Waypoints; // acculy iz IWaypointInterface*

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AActor*> Spawnpoints; // TODO: what exactly is a spawnpoint?!

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AActor*> Walls; // acculy iz IWallInterface*

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	TArray<AEvaCharacter*> Characters;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
	UDict* Settings;

	/** Returns the lua_State* associated with the character's team.
		lua_State objects are created per team, to enable communication between characters. */
	lua_State* GetLuaContextFor(AEvaCharacter* character);

	/** Loads the game with information from specified files */
	UFUNCTION(BlueprintCallable, Category = Game)
	void StartGame(FString ActorsFile, FString CfgFile);

};
