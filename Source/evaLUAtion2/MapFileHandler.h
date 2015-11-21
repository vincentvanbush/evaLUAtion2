// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Vector2Dpair.h"
#include "PowerupInfo.h"
#include <iostream>
#include <sstream>
#include "MapFileHandler.generated.h"

UCLASS()
class EVALUATION2_API AMapFileHandler : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapFileHandler();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	bool SaveMapFile(
		FString filename,
		TArray<int32> MapSize,
		TArray<FVector2Dpair> walls,
		TArray<FPowerupInfo> powerups
	);

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	bool LoadMapFile(
		FString filename,
		TArray<int32> &MapSize,
		TArray<FVector2D> &WaypointsCoords,
		TArray<FVector2Dpair> &WallsCoords,
		TArray<FPowerupInfo> &PowerupsCoords
	);

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	TArray<FString> GetMapsInFolder();

	bool ValidateMapFile(std::string Map);

};

/** Verify that the evaLUAtion2 directory in user's home folder exists.
If not, try to create it. Returns false if there's an error, true otherwise. */
static FORCEINLINE bool VerifyOrCreateGameDirectory(FString Folder, FString& OutFullPath)
{
	FString TestDir = FPlatformProcess::UserDir();
	TestDir += Folder;

	//Directory Exists?
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*TestDir))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*TestDir);

		if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*TestDir))
		{
			return false;
			//~~~~~~~~~~~~~~
		}
	}

	OutFullPath = TestDir;
	return true;
}

static FORCEINLINE bool VerifyMapsDirectory(FString &OutMapDirPath)
{
	FString RetPath;

	if (!VerifyOrCreateGameDirectory(FString("evaLUAtion2/"), RetPath))
		return false;

	if (!VerifyOrCreateGameDirectory(FString("evaLUAtion2/Maps/"), RetPath))
		return false;

	OutMapDirPath = RetPath;

	return true;
}