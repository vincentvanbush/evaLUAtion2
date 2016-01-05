// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "MapFileHandler.h"
#include "VictoryFileFunctions.h"

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
	TArray<FPowerupInfo> powerups,
	TArray<FWaypointInfo> waypoints,
	TArray<FWaypointsConnectionInfo> connections
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
	int WaypointsNumber = waypoints.Num();
	int ConnectionsNumber = connections.Num();

	ss << WaypointsNumber << "\n";
	for (int i = 0; i < WaypointsNumber; i++) {
		ss << "Index: " << waypoints[i].uniqueIndex << " PosX: " << waypoints[i].coord.X << " PosY: " << waypoints[i].coord.Y << "\n";
	}

	ss << ConnectionsNumber << "\n";
	for (int i = 0; i < ConnectionsNumber; i++) {
		ss << "m_iFrom: " << connections[i].from << " m_iTo: " << connections[i].to << " m_dCost: " << connections[i].cost << " m_iFlags: 0 ID: -1\n";
	}

	int WaypointPowerups = 0;
	int WaypointCounter = 0;
	/*for (int i = 0; i < PowerupsNumber; i++) {
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
	}*/

	ss << "\n" << MapSize[0] << " " << MapSize[1] << "\n";

	for (int i = 0; i < WallsNumber; i++) {
		ss << 0 << " ";
		ss << walls[i].Acoord.X << " " << walls[i].Acoord.Y << " ";
		ss << walls[i].Bcoord.X << " " << walls[i].Bcoord.Y << " ";
		ss << 1 << " " << 0 << "\n";
	}

	WaypointCounter = 0;
	// rozwi¹zaæ kwestiê poprawnych odnoœników do indeksów waypointów w sekcji powerupów
	for (int i = 0; i < PowerupsNumber; i++) {
		if (powerups[i].type != -1) { //nie jest waypointem
			ss << powerups[i].type << " " << 0 << " ";
			ss << powerups[i].coord.X << " " << powerups[i].coord.Y << " ";
			if (powerups[i].type != 4 && powerups[i].type != 5) {
				ss << 0 << " " << powerups[i].uniqueIndex << "\n";
				//WaypointCounter++;
			}
			else if (powerups[i].type == 4) {
				ss << 0 << " " << 0 << " " << powerups[i].uniqueIndex << "\n";
				//WaypointCounter++;
			}
			else if (powerups[i].type == 5) {
				ss << 0 << " " << -1 << "\n";
			}
		} //else {
			//WaypointCounter++;
		//}
		
	}

	SaveText = ss.str();
	return FFileHelper::SaveStringToFile(FString (SaveText.c_str()), *SaveDirectory);
}

bool AMapFileHandler::ValidateMapFile(string Map) {
	stringstream ss(stringstream::in | stringstream::out);
	stringstream line(stringstream::in | stringstream::out);
	stringstream line1(stringstream::in | stringstream::out);
	const int BUFFSIZE = 256;
	char buff[BUFFSIZE];
	int NumberOfLines;
	string sTemp;
	float fTemp;
	int iTemp;
	
	ss << Map;
	ss.getline(buff, BUFFSIZE);
	line << buff;
	line >> NumberOfLines;
	if (line.fail())
		return false;
	line.clear();
	for (int i = 0; i < NumberOfLines; i++) {
		ss.getline(buff, BUFFSIZE);
		line << buff;

		line >> sTemp;
		line >> iTemp;
		line >> sTemp;
		line >> fTemp;
		line >> sTemp;
		line >> fTemp;
		if (line.fail())
			return false;
		line >> sTemp;
		if (!line.eof())
			return false;
		line.clear();
	}

	ss.getline(buff, BUFFSIZE);
	line << buff;
	line >> NumberOfLines;
	if (line.fail())
		return false;
	line.clear();
	for (int i = 0; i < NumberOfLines; i++) {
		ss.getline(buff, BUFFSIZE);
		line << buff;

		line >> sTemp >> iTemp >> sTemp >> iTemp >> sTemp >> fTemp >> sTemp >> iTemp >> sTemp >> iTemp;
		if (line.fail())
			return false;
		line >> sTemp;
		if (!line.eof())
			return false;
		line.clear();
	}

	ss.getline(buff, BUFFSIZE);
	line << buff;
	line >> sTemp;
	if (!line.eof())
		return false;
	line.clear();

	ss.getline(buff, BUFFSIZE);
	line << buff;
	line >> iTemp >> iTemp;
	if (line.fail())
		return false;
	line >> sTemp;
	if (!line.eof())
		return false;
	line.clear();

	while (ss.getline(buff, BUFFSIZE)) {
		line << buff;

		line >> iTemp;
		if (line.fail())
			return false;
		if (iTemp == 0 || iTemp == 4) {
			line >> fTemp >> fTemp >> fTemp >> fTemp >> fTemp >> fTemp;
			if (line.fail())
				return false;
			line >> sTemp;
			if (!line.eof())
				return false;
		}
		else if (iTemp == 5 || iTemp == 6 || iTemp == 7 || iTemp == 8 || iTemp == 9) {
			line >> fTemp >> fTemp >> fTemp >> fTemp >> fTemp;
			if (line.fail())
				return false;
			line >> sTemp;
			if (!line.eof())
				return false;
		}
		line.clear();
	}

	return true;
}

FString AMapFileHandler::LoadMapFile(
	FString filename,
	TArray<int32> &MapSize,
	TArray<FWaypointInfo> &WaypointsCoords,
	TArray<FWaypointsConnectionInfo> &WaypointsConnections,
	TArray<FVector2Dpair> &WallsCoords,
	TArray<FPowerupInfo> &PowerupsCoords
	)
{
	// Verify that the game's directory exists in the user's home folder.
	FString loadDirectory;
	if (!VerifyMapsDirectory(loadDirectory))
		return FString("Maps directory missing");

	loadDirectory += filename;

	ifstream mapSource;
	string data, line;

	try {
		mapSource.open(TCHAR_TO_ANSI(*loadDirectory));
		if (mapSource.good()) {
			int counter = 0;


			mapSource >> counter;

			//Parse waypoints' positions
			while (counter > 0) {
				FWaypointInfo index;
				mapSource >> data;
				if (data != "Index:") return FString("Missing index value");
				mapSource >> index.uniqueIndex;
				mapSource >> data;
				if (data != "PosX:") return FString("Missing posX in index");
				mapSource >> index.coord.X;
				mapSource >> data;
				if (data != "PosY:") return FString("Missing posY in index");
				mapSource >> index.coord.Y;
				WaypointsCoords.Add(index);
				counter--;
			}

			mapSource >> counter;

			//Parse waypoints connections
			while (counter > 0) {
				FWaypointsConnectionInfo indexConnection;
				mapSource >> data;
				if (data != "m_iFrom:") return FString("Missing From in indexConnection");
				mapSource >> indexConnection.from;
				mapSource >> data;
				if (data != "m_iTo:") return FString("Missing To in indexConnection");
				mapSource >> indexConnection.to;
				mapSource >> data;
				if (data != "m_dCost:") return FString("Missing Cost in indexConnection");
				mapSource >> indexConnection.cost;
				//skip the rest
				mapSource >> data;
				if (data != "m_iFlags:") return FString("Missing Flags in indexConnection");
				mapSource >> data;
				mapSource >> data;
				if (data != "ID:") return FString("Missing Id in indexConnection");
				mapSource >> data;

				WaypointsConnections.Add(indexConnection);
				counter--;
			}

			//get map size
			int32 mapX, mapY;
			mapSource >> mapX >> mapY;
			MapSize.Add(mapX);
			MapSize.Add(mapY);

			//get powerups & walls
			//this is the tricky part where we have no idea how many elements there are, so we just read until the end of the file
			int type;
			while (!mapSource.eof() && mapSource >> type) {
				switch (type) {
				case 0:
				{
					FVector2Dpair vec;
					//wall
					//from x,y
					//to x,y
					mapSource >> vec.Acoord.X >> vec.Acoord.Y >> vec.Bcoord.X >> vec.Bcoord.Y >> data >> data;
					WallsCoords.Add(vec);
					break;
				}
				case 4:
				{
					//medkit
					FPowerupInfo vec;
					mapSource >> data >> vec.coord.X >> vec.coord.Y >> data >> data >> vec.uniqueIndex;
					vec.type = 4;
					PowerupsCoords.Add(vec);
					break;
				}
				case 5:
				{
					//spawn point
					FPowerupInfo vec;
					mapSource >> data >> vec.coord.X >> vec.coord.Y >> data >> vec.uniqueIndex;
					PowerupsCoords.Add(vec);
					break;
				}
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				{
					//weapons & armor
					FPowerupInfo vec;
					mapSource >> data >> vec.coord.X >> vec.coord.Y >> data >> vec.uniqueIndex;
					vec.type = type;
					PowerupsCoords.Add(vec);
					break;
				}
				default:
					return FString("Powerup with the given type is invalid");
				}
			}
		}
		else {
			return FString("Could not open the given map file");
		}
	}
	catch (...) {
		mapSource.close();
		return FString("Exception caught during map loading");
	}
	mapSource.close();
	return "OK";
}

TArray<FString> AMapFileHandler::GetMapsInFolder()
{
	FString Dir;
	VerifyMapsDirectory(Dir);

	TArray<FString> Names;
	UVictoryFileFunctions::GetFiles(Dir, Names, false, "emf");

	return Names;
}