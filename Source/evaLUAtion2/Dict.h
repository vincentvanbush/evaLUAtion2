// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Dict.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class EVALUATION2_API UDict : public UObject
{
	GENERATED_BODY()

	TMap<FString, FString> _map;

public:

	UFUNCTION(BlueprintCallable, Category = Dict)
		FString GetItem(FString key);

	UFUNCTION(BlueprintCallable, Category = Dict)
		void SetItem(FString key, FString val);
	
		
};
