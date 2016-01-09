// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Interfaces/PowerupInterface.h"
#include "EvaCharacter.h"
#include <lauxlib.h>
#include <luabind/error.hpp>
#include <map>
#include <iostream>
#include <sstream>
#include "NewCharacterInfo.h"
#include "Configuration.h"
#include "EvaGameState.generated.h"

/**
 * 
 */
UCLASS()
class EVALUATION2_API AEvaGameState : public AGameState
{
	GENERATED_BODY()

	std::map<int32, lua_State*> TeamLuaContexts;

	void LoadSettingsFromFile(FString CfgFile);

	float GameStartedAt;
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
		void Clear();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Game)
		float GetFloatTimeInSeconds();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<bool> stopAtTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<int32> numberOfParticles;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<float> arc;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<int32> ammoPacks;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<float> radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<int32> reloadTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<float> damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<int32> color;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<float> speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ConstArrays)
	TArray<int32> shootTime;

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
	AActor* FloorRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Config)
	UConfiguration* Configuration;

//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ExistingObjects)
//	UDict* Settings;

	/** Returns the lua_State* associated with the character's team.
		lua_State objects are created per team, to enable communication between characters. */
	lua_State* GetLuaContextFor(AEvaCharacter* character);

	/** Loads the game with information from specified files */
	UFUNCTION(BlueprintCallable, Category = Game)
	bool StartGame(
		FString CfgFile,
		TArray<FNewCharacterInfo> &CharactersInfo,
		FString &MapFile
	);

	bool LoadActorsFile(
		FString filename,
		FString ParentFolderPath,
		TArray<FNewCharacterInfo> &CharactersInfo
	);
};
