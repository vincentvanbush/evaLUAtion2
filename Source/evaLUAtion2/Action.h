// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "EvaCharacter.h"
#include "Misc.h"
#include "EvaGameState.h"
#include "Action.generated.h"

// class AEvaCharacter;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class EVALUATION2_API UAction : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = ActionProperties)
		AEvaCharacter *ControlledCharacter;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = ActionProperties)
		EActionType ActionType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = ActionProperties)
		bool IsBreakable;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = ActionProperties)
		bool IsRepeatable;

	UPROPERTY(BlueprintReadWrite, Category = ActionProperties)
		float ActionStarted;

	//how long does an action last in seconds
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = ActionProperties)
		float StandardCost;
	
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = ActionEvents)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ActionEvents)
		void OnEnter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = ActionEvents)
		bool CanExecuteExit(); // corresponds to Action::execute(...) in old evaLUAtion

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = ActionEvents)
		void OnExit();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Game)
		AEvaGameState* GameState;

};
