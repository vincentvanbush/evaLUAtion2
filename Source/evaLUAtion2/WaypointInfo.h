#pragma once

#include "WaypointInfo.generated.h"

USTRUCT(BlueprintType)
struct FWaypointInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector2D coord;

	UPROPERTY(BlueprintReadWrite)
		int32 type;

	UPROPERTY(BlueprintReadWrite)
		int32 uniqueIndex;

};