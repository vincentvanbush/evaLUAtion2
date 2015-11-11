#pragma once

#include "PowerupInfo.generated.h"

USTRUCT(BlueprintType)
struct FPowerupInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector2D coord;

	UPROPERTY(BlueprintReadWrite)
	int32 type;
};