// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "EvaCharacter.h"


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

Vector4d AEvaCharacter::getLongDestination() {
	return Vector4d(destination.X, destination.Y, destination.Z);
}