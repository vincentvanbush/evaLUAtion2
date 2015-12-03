#include "evaLUAtion2.h"
#include "ActorInfo.h"
#include "EvaCharacter.h"

ActorInfo::ActorInfo(AEvaCharacter * character) : name(character->getName()) {
	setDirection(character->getDirection());
	setPosition(character->getPosition());
	setTeam(character->team);
	setWeaponType(character->currentWeapon);
	setHealth(character->health);
	setArmour(character->armour);
}