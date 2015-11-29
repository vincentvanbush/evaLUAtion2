// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WallInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UWallInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class IWallInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Wall)
	FVector2D GetBeginLocation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Wall)
	FVector2D GetEndLocation();
};