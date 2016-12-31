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
	if (Trace(State->GetWorld(), nullptr, TraceStart, TraceEnd, Hit))
		return true;
	return false;
}

Vector4d Navigation::getNodePosition(int index)
{
	AActor* Waypoint = State->Waypoints[index];
	FVector Position = Waypoint->GetActorLocation();
	return Vector4d(Position);
}

int Navigation::getNumberOfTriggers()
{
	return State->Powerups.Num();
}

int Navigation::getNumberOfPoints()
{
	return State->Waypoints.Num();
}
#pragma optimize("", off)
Trigger* Navigation::getTrigger(int index)
{
	if (State->Powerups.IsValidIndex((uint32)index)) {
		AActor* Powerup = State->Powerups[index];
		return new Trigger(Powerup);
	}
	return NULL;
}
#pragma optimize("", on)
int Navigation::getNumberOfSpawnPoints()
{
	return State->Spawnpoints.Num();
}

Vector4d Navigation::getSpawnPoint(int index)
{
	return Vector4d(State->Spawnpoints[index]->GetActorLocation());
}


