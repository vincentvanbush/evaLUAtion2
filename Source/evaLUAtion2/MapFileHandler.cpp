// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "MapFileHandler.h"
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
	TArray<FVector2Dpair> walls,
	TArray<FPowerupInfo> powerups
	)
{
	FString SaveDirectory = "D:\\" + filename;
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

	ss << 0 << "\n\n" << 100 << " " << 100 << "\n";

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