// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WaypointInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UWaypointInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class IWaypointInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Waypoint)
	TArray<AActor*> GetConnections(); // acculy iz IWaypointInterface*
};