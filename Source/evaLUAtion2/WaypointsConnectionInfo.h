#pragma once

#include "WaypointsConnectionInfo.generated.h"

USTRUCT(BlueprintType)
struct FWaypointsConnectionInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 from;

	UPROPERTY(BlueprintReadWrite)
		int32 to;

	UPROPERTY(BlueprintReadWrite)
		float cost;
};