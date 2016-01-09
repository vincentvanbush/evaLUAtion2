#pragma once
#include "Trigger.h"
#include "EvaGameState.h"
#include "Misc.h"

class Navigation
{
private:
	AEvaGameState *State;

public:
	Navigation(AEvaGameState *state) { State = state; };
	Navigation(Navigation const&);
	void operator=(Navigation const&);
	bool anyRayCrateColision(Vector4d displacementVector, Vector4d positionVector);
	Vector4d getNodePosition(int index);
	int getNumberOfTriggers();
	int getNumberOfPoints();
	Trigger * getTrigger(int index);
	int getNumberOfSpawnPoints();
	Vector4d getSpawnPoint(int index);
};