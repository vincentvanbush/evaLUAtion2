// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "MapFileHandler.h"


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

bool AMapFileHandler::SaveMapFile(FString filename, FString SaveText)
{
	FString SaveDirectory = "D:\\" + filename;
	//FString SaveText = "dupa";

	return FFileHelper::SaveStringToFile(SaveText, *SaveDirectory);
}