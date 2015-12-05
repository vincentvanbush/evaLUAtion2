// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
//#include "EvaCharacter.h"
#include "Misc.h"
#include "Action.generated.h"

class AEvaCharacter;
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

	UPROPERTY(EditDefaultsOnly, Category = ActionProperties)
		EActionType ActionType;

	UPROPERTY(EditDefaultsOnly, Category = ActionProperties)
		bool IsBreakable;

	UPROPERTY(EditDefaultsOnly, Category = ActionProperties)
		bool IsRepeatable;

	UPROPERTY(BlueprintReadWrite, Category = ActionProperties)
		float ActionStarted;
	
	UFUNCTION(BlueprintImplementableEvent, Category = ActionEvents)
		void OnEnter();

	UFUNCTION(BlueprintImplementableEvent, Category = ActionEvents)
		bool CanExecuteExit(); // corresponds to Action::execute(...) in old evaLUAtion

	UFUNCTION(BlueprintImplementableEvent, Category = ActionEvents)
		void OnExit();
	
};
