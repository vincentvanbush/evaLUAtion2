// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc.h"
#include "ActionFactory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class EVALUATION2_API UActionFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Ebin)
	UAction* CreateAction(EActionType Type);
	
};
