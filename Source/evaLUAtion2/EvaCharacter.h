// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "evaLUAtion2.h"
#include "GameFramework/Character.h"
#include "Misc.h"
#include "Action.h"
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

	/** the number of frags for the character */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		int32 kills;

	/** the number of frags against the character */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		int32 killed;

	/** the number of character's friend kills */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		int32 friendkills;

	/** character's team identifier */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		int32 team;

	/** character's current destination point */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		FVector destination;

	/** character armour points */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		int32 armour;

	/** character health points */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		int32 health;

	/** character name */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		FString name;

	/** ammo[i] represents the current number of i-ty ammo type */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		TArray<int32> ammo;

	/** loaded[i] is true if the i-th weapon type is loaded */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		TArray<bool> loaded;

	Vector4d getLongDestination();

	// Konwersja pozycji z FVector, pobranej metod� GetActorLocation
	Vector4d getPosition() {
		return Vector4d(this->GetActorLocation());
	}

	Vector4d getDirection() {
		return Vector4d(this->GetActorRotation().Vector());
	}

	std::string getName() {
		std::string name(TCHAR_TO_UTF8(*name));
		return name;
	}

	/** The character's current weapon */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		EWeaponType currentWeapon;

	/** The character's current action */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		UAction *currentAction;

	/** The character's next action */
	UPROPERTY(BlueprintReadWrite, Category = CharacterState)
		UAction *nextAction;

	/** Called when the character has nothing to do or is doing a breakable action.
		Returns the next action to be performed.
		Corresponds to Actor::whatToDoNow from old evaLUAtion */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		UAction* decideNextAction();

	/** Change the character's weapon. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void selectWeapon(EWeaponType weapon);

	/** Start moving the character in a given direction. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void moveDirection(FVector direction);

	/** Start moving the character to a given position. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void moveTo(FVector target);

	/** Reload the character's weapon. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void reload();

	/** Rotate the character pointing to a given vector. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void rotate(FVector direction);

	/** Shoot at a given enemy character. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void shootAt(AEvaCharacter* enemy);

	/** Shoot at a given point. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void shootAtPoint(FVector vect);

	/** Turn the character into an idle state. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void wait();

	/** ??? */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = EvaluationActions)
		void continueAction();




private:

	
};