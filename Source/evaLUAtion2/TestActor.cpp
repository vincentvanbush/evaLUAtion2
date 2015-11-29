// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "TestActor.h"
#include "EvaGameState.h"


// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	AEvaGameState *state = GetWorld()->GetGameState<AEvaGameState>();
	AActor *actor = state->Powerups[0];

	// IPowerupInterface *test1 = Cast<IPowerupInterface>(actor);
	// ^ to nie dziala :C
	// per https://wiki.unrealengine.com/Interfaces_And_Blueprints
	if (actor->GetClass()->ImplementsInterface(UPowerupInterface::StaticClass()))
	{
		int32 ptype = IPowerupInterface::Execute_GetPowerupType(actor);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "The powerup's type is: " + FString::FromInt(ptype));
	}
	
}

// Called every frame
void ATestActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

