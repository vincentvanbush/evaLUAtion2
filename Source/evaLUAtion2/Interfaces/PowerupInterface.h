// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerupInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UPowerupInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class IPowerupInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Powerup)
	int32 GetPowerupType();
};