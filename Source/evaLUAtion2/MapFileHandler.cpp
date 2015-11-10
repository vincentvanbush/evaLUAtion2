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

bool AMapFileHandler::SaveMapFile(FString filename, TArray<FVector2Dpair> walls)
{
	FString SaveDirectory = "D:\\" + filename;
	string SaveText = "";
	stringstream ss(stringstream::in | stringstream::out);
	ss << 0 << "\n" << 0 << "\n\n" << 1000 << " " << 1000 << "\n";



	int WallsNumber = walls.Num();
	for (int i = 0; i < WallsNumber; i++) {
		ss << 0 << " ";
		ss << walls[i].Acoord.X << " " << walls[i].Acoord.Y << " ";
		ss << walls[i].Bcoord.X << " " << walls[i].Bcoord.Y << " ";
		ss << 1 << " " << 0 << "\n";
	}

	SaveText = ss.str();
	return FFileHelper::SaveStringToFile(FString (SaveText.c_str()), *SaveDirectory);
}