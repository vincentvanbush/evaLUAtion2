// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "EvaCharacter.h"
#include "Misc.h"

// Sets default values
AEvaCharacter::AEvaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEvaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEvaCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AEvaCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

Vector4d AEvaCharacter::getLongDestination() 
{
	return Vector4d(destination.X, destination.Y, destination.Z);
}

UAction* AEvaCharacter::decideNextAction_Implementation()
{
	// corresponds to whatToDoNow method in old evaLUAtion
	return nullptr;
};

void AEvaCharacter::selectWeapon_Implementation(EWeaponType weapon)
{
	// TODO: implement here or in BP
};

void AEvaCharacter::moveDirection_Implementation(FVector direction)
{
	// TODO: implement here or in BP
};

void AEvaCharacter::moveTo_Implementation(FVector target)
{
	// TODO: implement here or in BP
};

void AEvaCharacter::reload_Implementation()
{
	// TODO: implement here or in BP
};

void AEvaCharacter::rotate_Implementation(FVector direction)
{
	// TODO: implement here or in BP
};

void AEvaCharacter::shootAt_Implementation(AEvaCharacter* enemy)
{
	// TODO: implement here or in BP
};

void AEvaCharacter::shootAtPoint_Implementation(FVector vect)
{
	// TODO: implement here or in BP
};

void AEvaCharacter::wait_Implementation()
{
	// TODO: implement here or in BP
};

void AEvaCharacter::continueAction_Implementation()
{
	// TODO: implement here or in BP
};