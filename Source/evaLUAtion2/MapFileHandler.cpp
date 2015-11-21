// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "MapFileHandler.h"
#include "VictoryFileFunctions.h"
#include <iostream>
#include <sstream>
using namespace	std;

// Sets default values
AMapFileHandler::AMapFileHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapFileHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapFileHandler::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AMapFileHandler::SaveMapFile(
	FString filename, 
	TArray<int32> MapSize,
	TArray<FVector2Dpair> walls,
	TArray<FPowerupInfo> powerups
	)
{
	// Verify that the game's directory exists in the user's home folder.
	FString TestDir;
	if (!VerifyMapsDirectory(TestDir))
		return false;
	
	FString SaveDirectory = TestDir + filename;
	string SaveText = "";
	stringstream ss(stringstream::in | stringstream::out);
	int WallsNumber = walls.Num();
	int PowerupsNumber = powerups.Num();
	int WaypointPowerups = 0;
	int WaypointCounter = 0;
	for (int i = 0; i < PowerupsNumber; i++) {
		if (powerups[i].type != 5) {
			WaypointPowerups++;
		}
	}
	ss << WaypointPowerups << "\n";
	for (int i = 0; i < PowerupsNumber; i++) {
		if (powerups[i].type != 5) {
			ss << "Index: " << WaypointCounter << " PosX: " << powerups[i].coord.X << " PosY: " << powerups[i].coord.Y << "\n";
			WaypointCounter++;
		}
	}

	ss << 0 << "\n\n" << MapSize[0] << " " << MapSize[1] << "\n";

	for (int i = 0; i < WallsNumber; i++) {
		ss << 0 << " ";
		ss << walls[i].Acoord.X << " " << walls[i].Acoord.Y << " ";
		ss << walls[i].Bcoord.X << " " << walls[i].Bcoord.Y << " ";
		ss << 1 << " " << 0 << "\n";
	}

	WaypointCounter = 0;
	for (int i = 0; i < PowerupsNumber; i++) {
		if (powerups[i].type != -1) { //nie jest waypointem
			ss << powerups[i].type << " " << 0 << " ";
			ss << powerups[i].coord.X << " " << powerups[i].coord.Y << " ";
			if (powerups[i].type != 4 && powerups[i].type != 5) {
				ss << 0 << " " << WaypointCounter << "\n";
				WaypointCounter++;
			}
			else if (powerups[i].type == 4) {
				ss << 0 << " " << 0 << " " << WaypointCounter << "\n";
				WaypointCounter++;
			}
			else if (powerups[i].type == 5) {
				ss << 0 << " " << -1 << "\n";
			}
		} else {
			WaypointCounter++;
		}
		
	}

	SaveText = ss.str();
	return FFileHelper::SaveStringToFile(FString (SaveText.c_str()), *SaveDirectory);
}

bool AMapFileHandler::LoadMapFile(
	FString filename,
	TArray<int32> &MapSize,
	TArray<FVector2D> &WaypointsCoords,
	TArray<FVector2Dpair> &WallsCoords,
	TArray<FPowerupInfo> &PowerupsCoords
	)
{
	// Verify that the game's directory exists in the user's home folder.
	FString LoadDirectory;
	if (!VerifyMapsDirectory(LoadDirectory))
		return false;

	LoadDirectory += filename;
	FString loaded;
	if (!FFileHelper::LoadFileToString(loaded, *LoadDirectory))
		return false;

	// TODO: Make this fail-safe. I mean, validate the input.
	string LoadedText(TCHAR_TO_UTF8(*loaded));
	stringstream ss(stringstream::in | stringstream::out);
	ss << LoadedText;

	string temp;
	int ObjectType;
	int WallsCounter = 0;

	int NumberOfLines;
	FVector2D Vec;
	ss >> NumberOfLines;
	for (int i = 0; i < NumberOfLines; i++) {
		ss >> temp >> temp >> temp >> Vec.X >> temp >> Vec.Y;
		WaypointsCoords.Add(Vec);
	}
	
	ss >> NumberOfLines;
	for (int i = 0; i < NumberOfLines; i++) {
		ss >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;
	}
	
	int32 MapCoord;
	ss >> MapCoord;
	MapSize.Add(MapCoord);
	ss >> MapCoord;
	MapSize.Add(MapCoord);

	FVector2Dpair VecPair;
	FPowerupInfo Powerup;
	while (ss) {
		ss >> ObjectType;
		if (ObjectType == 0) {
			ss >> VecPair.Acoord.X;
			ss >> VecPair.Acoord.Y;
			ss >> VecPair.Bcoord.X;
			ss >> VecPair.Bcoord.Y;
			WallsCoords.Add(VecPair);
			WallsCounter++;
			ss >> temp >> temp;
		}
		else if (ObjectType == 4) {
			ss >> temp >> Powerup.coord.X >> Powerup.coord.Y >> temp >> temp >> temp;
			Powerup.type = 4;
			PowerupsCoords.Add(Powerup);
		}
		else if (ObjectType == 6 || ObjectType == 7 || ObjectType == 8 || ObjectType == 9) {
			ss >> temp >> Powerup.coord.X >> Powerup.coord.Y >> temp >> temp;
			Powerup.type = ObjectType;
			PowerupsCoords.Add(Powerup);
		}
	}
	return true;
}

TArray<FString> AMapFileHandler::GetMapsInFolder()
{
	FString Dir;
	VerifyMapsDirectory(Dir);

	TArray<FString> Names;
	UVictoryFileFunctions::GetFiles(Dir, Names, false, "emf");

	return Names;
}