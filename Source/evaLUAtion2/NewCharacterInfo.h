#pragma once

#include "NewCharacterInfo.generated.h"

USTRUCT(BlueprintType)
struct FNewCharacterInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString CharacterName;

	UPROPERTY(BlueprintReadWrite)
	FString ScriptFile;

	UPROPERTY(BlueprintReadWrite)
	int32 Team;

	UPROPERTY(BlueprintReadWrite)
	FVector2D Position;
};