#pragma once
#include "Misc.h"

class Trigger
{
private:
	AActor *UnderlyingPowerup;
public:
	Trigger(AActor *Powerup);
	enum class TriggerType : int {
		Weapon = 0,
		Armour = 1,
		Health = 2,
		Invalid = -1
	};

	static int8 weapon() { return 0; };
	static int8 armour() { return 1; };
	static int8 health() { return 2; };

	int getType();
	bool isActive();
	Vector4d getPosition();
	double getBoundingRadius();
	bool isValid();
};