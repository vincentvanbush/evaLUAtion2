#include "evaLUAtion2.h"
#include "Navigation.h"
#include "EvaGameState.h"
#include "Interfaces/WaypointInterface.h"

bool Navigation::anyRayCrateColision(Vector4d displacementVector, Vector4d positionVector)
{
	FVector TraceStart(positionVector.val[0], positionVector.val[1], positionVector.val[2]);
	FVector Displacement(displacementVector.val[0], displacementVector.val[1], displacementVector.val[2]);
	FVector TraceEnd = TraceStart + Displacement;
	FHitResult Hit;
	if (Trace(GEngine->GetWorld(), nullptr, TraceStart, TraceEnd, Hit))
		return true;
	return false;
}

Vector4d Navigation::getNodePosition(int index)
{
	AEvaGameState* State = GEngine->GetWorld()->GetGameState<AEvaGameState>();
	AActor* Waypoint = State->Waypoints[index];
	FVector Position = Waypoint->GetActorLocation();
	return Vector4d(Position);
}

int Navigation::getNumberOfTriggers()
{
	AEvaGameState* State = GEngine->GetWorld()->GetGameState<AEvaGameState>();
	return State->Powerups.Num();
}

int Navigation::getNumberOfPoints()
{
	AEvaGameState* State = GEngine->GetWorld()->GetGameState<AEvaGameState>();
	return State->Waypoints.Num();
}

Trigger* Navigation::getTrigger(int index)
{
	AEvaGameState* State = GEngine->GetWorld()->GetGameState<AEvaGameState>();
	AActor* Powerup = State->Powerups[index];
	return new Trigger(Powerup);
}

int Navigation::getNumberOfSpawnPoints()
{
	AEvaGameState* State = GEngine->GetWorld()->GetGameState<AEvaGameState>();
	return State->Spawnpoints.Num();
}

Vector4d Navigation::getSpawnPoint(int index)
{
	AEvaGameState* State = GEngine->GetWorld()->GetGameState<AEvaGameState>();
	return Vector4d(State->Waypoints[index]->GetActorLocation());
}


