#pragma once

#include "Vector2Dpair.generated.h"

USTRUCT(BlueprintType)
struct FVector2Dpair
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector2D Acoord;

	UPROPERTY(BlueprintReadWrite)
	FVector2D Bcoord;
};