// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Vector2Dpair.h"
#include "PowerupInfo.h"
#include "WaypointInfo.h"
#include "WaypointsConnectionInfo.h"
#include "AppConfig.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
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

	/** Verify that the evaLUAtion2 directory in user's home folder exists.
	If not, try to create it. Returns false if there's an error, true otherwise. */
	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	static bool VerifyOrCreateGameDirectory(FString Folder, FString& OutFullPath)
	{

		FString ValueReceived;
		bool res = UAppConfig::GetGameIniStr("Paths", "UserData", ValueReceived);

		FString TestDir;

		if (!res || ValueReceived == "Home")
		{
			TestDir = FPlatformProcess::UserDir();
		}
		else if (ValueReceived == "GameDir")
		{
			TestDir = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
		}
		else
		{
			TestDir = ValueReceived;
		}
		
		// 
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

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	bool SaveMapFile(
		FString filename,
		TArray<int32> MapSize,
		TArray<FVector2Dpair> walls,
		TArray<FPowerupInfo> powerups,
		TArray<FWaypointInfo> waypoints,
		TArray<FWaypointsConnectionInfo> connections
	);

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	FString LoadMapFile(
		FString filename,
		TArray<int32> &MapSize,
		TArray<FWaypointInfo> &WaypointsCoords,
		TArray<FWaypointsConnectionInfo> &WaypointsConnections,
		TArray<FVector2Dpair> &WallsCoords,
		TArray<FPowerupInfo> &PowerupsCoords
	);

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	TArray<FString> GetMapsInFolder();


	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	static bool VerifyMapsDirectory(FString &OutMapDirPath)
	{
		FString RetPath;

		if (!VerifyOrCreateGameDirectory(FString("evaLUAtion2/"), RetPath))
			return false;

		if (!VerifyOrCreateGameDirectory(FString("evaLUAtion2/Maps/"), RetPath))
			return false;

		OutMapDirPath = RetPath;

		return true;
	}

	UFUNCTION(BlueprintCallable, Category = VictoryFileFunctions)
	static bool VerifyProfilesDirectory(FString &OutMapDirPath)
	{
		FString RetPath;

		if (!VerifyOrCreateGameDirectory(FString("evaLUAtion2/"), RetPath))
			return false;

		if (!VerifyOrCreateGameDirectory(FString("evaLUAtion2/Profiles/"), RetPath))
			return false;

		OutMapDirPath = RetPath;

		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	static bool VerifyScriptsDirectory(FString &OutMapDirPath)
	{
		FString RetPath;

		if (!VerifyOrCreateGameDirectory(FString("evaLUAtion2/"), RetPath))
			return false;

		if (!VerifyOrCreateGameDirectory(FString("evaLUAtion2/Scripts/"), RetPath))
			return false;

		OutMapDirPath = RetPath;

		return true;
	}

	bool ValidateMapFile(std::string Map);

};
