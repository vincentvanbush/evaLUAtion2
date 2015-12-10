#include "evaLUAtion2.h"
#include "ActorKnowledge.h"
#include <set>
//#include "main/Configuration.h"
//#include "entities/Actor.h"
//#include "main/GameFactory.h"
//#include "main/RandomGenerator.h"

ActorKnowledge::ActorKnowledge(AEvaCharacter * character) : character(character) {
}

Vector4d ActorKnowledge::getPosition() {
	return character->getPosition();
}

Vector4d ActorKnowledge::getDirection() {
	return character->getDirection();
}

int ActorKnowledge::getHealth() {
	return character->health;
}

int ActorKnowledge::getArmour() {
	return character->armour;
}

uint8 ActorKnowledge::getWeaponType() {
	return static_cast<uint8>(character->currentWeapon);
}

int ActorKnowledge::getAmmo(EWeaponType type) {
	return character->ammo[(int)type];
}

bool ActorKnowledge::isLoaded(EWeaponType type) {
	return character->loaded[(int)type];
}

unsigned short ActorKnowledge::getTeam() {
	return (unsigned short)character->team;
}

const char * ActorKnowledge::getName() {
	return character->getName().c_str();
}

ActorInfo ActorKnowledge::getSelf() {
	return character->getActorInfo();
}

Vector4d ActorKnowledge::getLongDestination() {
	return character->getLongDestination();
}