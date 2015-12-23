#include "evaLUAtion2.h"
#include "Trigger.h"
#include "EvaGameState.h"

// TODO: the Powerup interface should contain all the things that we need to know about
// what the old evaluation called 'Triggers' :)))))))

Trigger::Trigger(AActor *Powerup)
{
	UnderlyingPowerup = Powerup;
}

int Trigger::getType()
{
	if (isValid())
	{
		int32 PowerupType = IPowerupInterface::Execute_GetPowerupType(UnderlyingPowerup);
		if (PowerupType >= 6 && PowerupType <= 9)
			return 0; // weapon
		else if (PowerupType == 4)
			return 2; // health
		else if (PowerupType == 10)
			return 1; // armour
	}
	return -1;
}

bool Trigger::isActive()
{
	if (isValid())
	{
		if (IPowerupInterface::Execute_IsActive(UnderlyingPowerup))
			return true;
	}
	return false;
}

Vector4d Trigger::getPosition()
{
	return Vector4d(UnderlyingPowerup->GetActorLocation());
}

double Trigger::getBoundingRadius()
{
	if (isValid())
	{
		return IPowerupInterface::Execute_GetBoundingRadius(UnderlyingPowerup);
	}
	return -1.0f;
}

bool Trigger::isValid()
{
	if (UnderlyingPowerup != nullptr
		&& UnderlyingPowerup->GetClass()->ImplementsInterface(UPowerupInterface::StaticClass())) {
		return true;
	}
	return false;
}