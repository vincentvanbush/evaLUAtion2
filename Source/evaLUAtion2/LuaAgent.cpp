// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "LuaAgent.h"
#include <iostream>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include "Misc.h"
#include <vector>
#include "ActorInfo.h"

#pragma warning(disable: 4541)
using namespace luabind;

typedef std::vector<ActorInfo>::reference(std::vector<ActorInfo>:: *AtFunctionType)(std::vector<ActorInfo>::size_type);


lua_State * ULuaAgent::createLuaEnv() {
	lua_State * pL = luaL_newstate();
	luaL_openlibs(pL);
	open(pL);
	module(pL)
		[
			class_<Enumerations>("Enumerations")
			.enum_("ActionType")
			[
				value("Moving", 0),
				value("Shooting", 1),
				value("ChangingWeapon", 2),
				value("Dying", 3),
				value("Reloading", 4),
				value("Waiting", 5)
			]
			.enum_("WeaponType")
				[
					value("Chaingun", 0),
					value("Railgun", 1),
					value("RocketLuncher", 2),
					value("Shotgun", 3),
					value("WeaponSize", 4)
				]
			/*,
				class_<std::vector<ActorInfo> >("vectorOfActorInfo")
				.def("size", &std::vector<ActorInfo>::size)
				.def("at", (AtFunctionType)&std::vector<ActorInfo>::at)
				,
				class_<std::vector<int> >("vectorOfInt")
				.def("size", &std::vector<int>::size)
				.def("at", (int&(std::vector<int>::*)(size_t))&std::vector<int>::at)
				,
				class_<ActorInfo>("ActorInfo")
				.def(constructor<>())

				.def("getHealth", &ActorInfo::getHealth)
				.def("getPosition", &ActorInfo::getPosition)
				.def("getDirection", &ActorInfo::getDirection)
				//			.def("getActionType", &ActorInfo::getActionType)
				.def("getTeam", &ActorInfo::getTeam)
				.def("getName", &ActorInfo::getName)
				.def("getWeaponType", &ActorInfo::getWeaponType)

				.def("setHealth", &ActorInfo::setHealth)
				.def("setPosition", &ActorInfo::setPosition)
				.def("setDirection", &ActorInfo::setDirection)
				//			.def("setActionType", &ActorInfo::setActionType)
				.def("setTeam", &ActorInfo::setTeam)
				.def("setWeaponType", &ActorInfo::setWeaponType)*/
				/*,
				 TODO uncomment when ready
				class_<ActorKnowledge>("ActorKnowledge")
				.def("getName", &ActorKnowledge::getName)
				.def("getPosition", &ActorKnowledge::getPosition)
				.def("getDirection", &ActorKnowledge::getDirection)
				//			.def("getActionType", &ActorKnowledge::getActionType)
				.def("getTeam", &ActorKnowledge::getTeam)
				.def("getWeaponType", &ActorKnowledge::getWeaponType)
				.def("getHealth", &ActorKnowledge::getHealth)
				.def("getAmmo", &ActorKnowledge::getAmmo)
				.def("getSeenFriends", &ActorKnowledge::getSeenFriends)
				.def("getSeenFoes", &ActorKnowledge::getSeenFoes)
				.def("getEstimatedTimeToReach", &ActorKnowledge::getEstimatedTimeToReach)
				.def("getSelf", &ActorKnowledge::getSelf)
				.def("getNavigation", &ActorKnowledge::getNavigation)
				.def("getArmour", &ActorKnowledge::getArmour)
				.def("isMoving", &ActorKnowledge::isMoving)
				.def("isLoaded", &ActorKnowledge::isLoaded)
				.def("getLongDestination", &ActorKnowledge::getLongDestination)
				.def("getShortDestination", &ActorKnowledge::getShortDestination)
				,
				class_<Trigger>("Trigger")
				.enum_("TriggerType")
				[
					value("Weapon", 0),
					value("Armour", 1),
					value("Health", 2)
				]
			.def("getType", &Trigger::getType)
				.def("isActive", &Trigger::isActive)
				.def("getPosition", &Trigger::getPosition)
				.def("getBoundingRadius", &Trigger::getBoundingRadius)
				,
				class_<Navigation>("Navigation")
				.def("anyRayCrateColision", &Navigation::anyRayCrateColision)
				.def("getNodePosition", &Navigation::getNodePosition)
				.def("searchWay", (std::vector<int>(Navigation:: *)(Vector4d, Vector4d)) &Navigation::searchWay)
				.def("getNumberOfTriggers", &Navigation::getNumberOfTriggers)
				.def("getTrigger", &Navigation::getTrigger)
				.def("getNumberOfSpawnPoints", &Navigation::getNumberOfSpawnPoints)
				.def("getSpawnPoint", &Navigation::getSpawnPoint)
				.def("getNumberOfPoints", &Navigation::getNumberOfPoints)
				*/,
				class_<ULuaAgent>("LuaAgent")
				/*.def("randomDouble", &ULuaAgent::randomDouble)
				.def("selectWeapon", &ULuaAgent::selectWeapon)
				.def("moveDirection", &ULuaAgent::moveDirection)*/
				.def("moveTo", &ULuaAgent::moveTo)
				/*.def("reload", &ULuaAgent::reload)
				.def("rotate", &ULuaAgent::rotate)
				.def("shootAt", &ULuaAgent::shootAt)
				.def("shootAtPoint", &ULuaAgent::shootAtPoint)
				.def("wait", &ULuaAgent::wait)
				.def("continueAction", &ULuaAgent::continueAction)*/
				,
				class_<Vector4d>("Vector4d")
				.def("value", &Vector4d::value)
				.def(constructor<double, double, double, double>())
				.def("dot", &Vector4d::dot)
				.def("length", &Vector4d::length)
				.def("lengthSquared", &Vector4d::lengthSquared)
				.def("normal", &Vector4d::normal)
				.def("normalize", &Vector4d::normalize)
				.def(self * double())
				.def(self / double())
				.def(self + other<Vector4d>())
				.def(self - other<Vector4d>())
				.def(self == other<Vector4d>())
		];
	return pL;
	return pL;
}

AEvaCharacter* ULuaAgent::GetControlledCharacter()
{
	return Cast<AEvaCharacter>(GetOwner());
}

void ULuaAgent::Initialize(FString filename)
{
	lua_State *pL = ULuaAgent::createLuaEnv();

	std::string name(TCHAR_TO_UTF8(*filename));

	int error = luaL_loadfile(pL, name.c_str()) || lua_pcall(pL, 0, LUA_MULTRET, 0);
	if (error) {
		std::cerr << "[Lua] Error " << error << ": " << lua_tostring(pL, -1) << " - during execution of script: " << name << "\n";
		lua_pop(pL, 1);  /* pop error message from the stack */
	}
	this->luaEnv = pL;
	
	name.resize(name.length() - 4);

	FString baseName = FPaths::GetBaseFilename(filename);
	std::string stdBaseName(TCHAR_TO_UTF8(*baseName));
	whatToName = std::string(stdBaseName + "whatTo");
	onStartName = std::string(stdBaseName + "onStart");
}

void ULuaAgent::whatToDo()
{
	FString wtn(UTF8_TO_TCHAR(whatToName.c_str()));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, wtn);

	// Call the function in the lua script.
	try {
		call_function<void>(luaEnv,	whatToName.c_str(),	this/* TODO: actorKnowledge, time */);
	}
	catch (error& e) {
		FString errMsg(e.what());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, errMsg);
	}
}

void ULuaAgent::onStart()
{
	
}

void ULuaAgent::selectWeapon(EWeaponType weapon)
{
	
}

void ULuaAgent::moveDirection(Vector4d direction)
{
	
}

void ULuaAgent::moveTo(Vector4d target)
{
	FVector TargetFV(target.val[0], target.val[1], target.val[2]);
	GetControlledCharacter()->moveTo(TargetFV);
}

void ULuaAgent::reload()
{

}

void ULuaAgent::rotate(Vector4d direction)
{

}

void ULuaAgent::shootAt(ActorInfo enemy)
{

}

void ULuaAgent::shootAtPoint(Vector4d vect)
{

}

void ULuaAgent::wait()
{

}

void ULuaAgent::continueAction()
{

}
