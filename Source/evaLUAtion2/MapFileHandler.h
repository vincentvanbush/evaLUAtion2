// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Vector2Dpair.h"
#include "PowerupInfo.h"
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
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	bool SaveMapFile(
		FString filename,
		TArray<int32> MapSize,
		TArray<FVector2Dpair> walls,
		TArray<FPowerupInfo> powerups
	);

	UFUNCTION(BlueprintCallable, Category = "FilesHandling")
	void LoadMapFile(
		TArray<int32> &MapSize,
		TArray<FVector2D> &WaypointsCoords,
		TArray<FVector2Dpair> &WallsCoords,
		FString &text,
		float &a,
		float b
	);
	
};
