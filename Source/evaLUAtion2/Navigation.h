#pragma once
#include "Trigger.h"
#include "Misc.h"

class Navigation
{
public:
	bool anyRayCrateColision(Vector4d displacementVector, Vector4d positionVector);
	Vector4d getNodePosition(int index);
	int getNumberOfTriggers();
	int getNumberOfPoints();
	Trigger * getTrigger(int index);
	int getNumberOfSpawnPoints();
	Vector4d getSpawnPoint(int index);
};