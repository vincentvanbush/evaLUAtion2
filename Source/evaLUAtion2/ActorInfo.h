#pragma once

#include <string>
#include <vector>
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

// These are a sort of wrappers around vector template types
// because for some weird reason Lua throws a "Trying to use
// unregistered class" error when calling vector methods...

class ActorInfoVectorWrapper
{
private:
	std::vector<ActorInfo> _vec;
public:
	ActorInfoVectorWrapper(std::vector<ActorInfo> v)
	{
		_vec = v;
	}
	int size() { return _vec.size(); };
	ActorInfo at(int index) { return _vec.at(index); };
};

class IntVectorWrapper
{
private:
	std::vector<int> _vec;
public:
	IntVectorWrapper(std::vector<int> v)
	{
		_vec = v;
	}
	int size() { return _vec.size(); };
	int at(int index) { return _vec.at(index); };
};