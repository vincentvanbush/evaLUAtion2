// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "EvaCharacter.h"
#include "ActorInfo.h"
#include "LuaAgent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class EVALUATION2_API ULuaAgent : public UActorComponent
{
	GENERATED_BODY()

public:

	/** Corresponds to old evaLUAtion's constructor of LuaAgent.
		Should create all the Lua environment, bind classes, etc. */
	UFUNCTION(BlueprintCallable, Category = "Lua Agent")
	void Initialize(FString &filename /*, lua_State * pL*/); // TODO: uncomment this when ready

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lua Agent")
	bool IsEnabled;

	/** Called by decideNextAction, should use the 'whatTo' method in the Lua script. */
	UFUNCTION(BlueprintCallable, Category = "Lua Agent")
	void whatToDo();

	/** Should use the 'onStart' method in the Lua script. */
	UFUNCTION(BlueprintCallable, Category = "Lua Agent")
	void onStart();

	// The following methods should be exposed to the scripting api

	double randomDouble();
	void selectWeapon(EWeaponType weapon);
	void moveDirection(Vector4d direction);
	void moveTo(Vector4d target);
	void reload();
	void rotate(Vector4d direction);
	void shootAt(ActorInfo enemy);
	void shootAtPoint(Vector4d vect);
	void wait();
	void continueAction();
	
private:
	
	/** Returns the character controlled by the agent.
		The character object has all the methods that correspond to the LuaAgent methods,
		which should be called in order to actually manipulate the character in UE4 world. */
	AEvaCharacter *GetControlledCharacter();

	/** Constructs the ActorKnowledge object that should be passed to the Lua script. */
	// ActorKnowledge *ConstructActorKnowledge();
	// TODO: uncomment this when ActorKnowledge class is ready
	
	
};
