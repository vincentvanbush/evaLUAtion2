#pragma once

#include <string>
#include "Misc.h"

class AEvaCharacter;
class ActorInfo
{
public:
	ActorInfo() {}
	ActorInfo(AEvaCharacter * character);
	Vector4d getPosition() {
		return position;
	}
	Vector4d getDirection() {
		return direction;
	}
	void setPosition(Vector4d position) {
		this->position = position;
	}
	void setDirection(Vector4d direction) {
		this->direction = direction;
	}
	unsigned short getTeam() {
		return team;
	}
	void setTeam(int team) {
		this->team = (unsigned short)team;
	}
	int getHealth() {
		return health;
	}
	void setHealth(int health) {
		this->health = health;
	}
	int getArmour() {
		return armour;
	}
	void setArmour(int armour) {
		this->armour = armour;
	}
	const char* getName() {
		return name.c_str();
	}
	uint8 getWeaponType() { // actually is EWeaponType converted to uint8
		return static_cast<uint8>(weaponType);
	}
	void setWeaponType(EWeaponType type) {
		this->weaponType = type;
	}
	virtual ~ActorInfo() {}
	bool operator<(const ActorInfo& q) const {
		return name < q.name;//TODO !!! to inaczej zrobiæ
	}
protected:
	int armour;
	std::string name;
	Vector4d position;
	Vector4d direction;
	unsigned short team;
	int health;
	EWeaponType weaponType;
	

};