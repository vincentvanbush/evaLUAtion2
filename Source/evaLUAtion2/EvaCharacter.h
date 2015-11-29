// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "evaLUAtion2.h"
#include "GameFramework/Character.h"
#include "Misc.h"
#include <string>
#include "EvaCharacter.generated.h"

UCLASS()
class EVALUATION2_API AEvaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEvaCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(BlueprintReadWrite)
		int32 kills;

	UPROPERTY(BlueprintReadWrite)
		int32 killed;

	UPROPERTY(BlueprintReadWrite)
		int32 friendkills;

	UPROPERTY(BlueprintReadWrite)
		int32 team;

	UPROPERTY(BlueprintReadWrite)
		FVector destination;

	UPROPERTY(BlueprintReadWrite)
		int32 armour;

	UPROPERTY(BlueprintReadWrite)
		int32 health;

	UPROPERTY(BlueprintReadWrite)
		FString name;

	Vector4d getLongDestination();

	Vector4d getPosition() {
		return position;
	}
	Vector4d getDirection() {
		return direction;
	}
	Enumerations::WeaponType getCurrentWeapon() {
		return currentWeapon;
	}
	std::string getName() {
		std::string name(TCHAR_TO_UTF8(*name));
		return name;
	}
	void setCurrentWeapon(Enumerations::WeaponType weapon) {
		currentWeapon = weapon;
	}
	void setPosition(Vector4d position) {
		this->position = position;
	}
	void setDirection(Vector4d direction) {
		this->direction = direction;
	}

private:
	Vector4d position;
	Vector4d direction;
	Enumerations::WeaponType currentWeapon;
	
};
