// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "LuaAgent.h"
#include <iostream>
#include <sstream>
#include "EvaGameState.h"

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include "Misc.h"
#include <vector>
//#include "ActorInfo.h"
#include "ActorKnowledge.h"
#include "Navigation.h"

#pragma warning(disable: 4541)
using namespace luabind;

typedef std::vector<ActorInfo>::reference(std::vector<ActorInfo>:: *AtFunctionType)(std::vector<ActorInfo>::size_type);
typedef std::vector<ActorInfo>::size_type(std::vector<ActorInfo>:: *SizeFunctionType)();


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
			,
				class_<ActorInfoVectorWrapper >("vectorOfActorInfo")
				.def("size", &ActorInfoVectorWrapper::size)
				.def("at", &ActorInfoVectorWrapper::at)
				,
				class_<IntVectorWrapper >("vectorOfInt")
				.def("size", &IntVectorWrapper::size)
				.def("at", &IntVectorWrapper::at)
				,
				class_<ActorInfo>("ActorInfo")
				.def(constructor<>())

				.def("getHealth", &ActorInfo::getHealth)
				.def("getPosition", &ActorInfo::getPosition)
				.def("getDirection", &ActorInfo::getDirection)
				.def("getTeam", &ActorInfo::getTeam)
				.def("getName", &ActorInfo::getName)
				.def("getWeaponType", &ActorInfo::getWeaponType)
				.def("setHealth", &ActorInfo::setHealth)
				.def("setPosition", &ActorInfo::setPosition)
				.def("setDirection", &ActorInfo::setDirection)
				.def("setTeam", &ActorInfo::setTeam)
				.def("setWeaponType", &ActorInfo::setWeaponType)
				,
				// TODO uncomment when ready
				class_<ActorKnowledge>("ActorKnowledge")
				.def("getActionType", &ActorKnowledge::getActionType)
				.def("getName", &ActorKnowledge::getName)
				.def("getPosition", &ActorKnowledge::getPosition)
				.def("getDirection", &ActorKnowledge::getDirection)
				.def("getTeam", &ActorKnowledge::getTeam)
				.def("getWeaponType", &ActorKnowledge::getWeaponType)
				.def("getHealth", &ActorKnowledge::getHealth)
				.def("getAmmo", &ActorKnowledge::getAmmo)
				.def("getSeenActors", &ActorKnowledge::getSeenActors)
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
				//.def("searchWay", (std::vector<int>(Navigation:: *)(Vector4d, Vector4d)) &Navigation::searchWay)
				.def("getNumberOfTriggers", &Navigation::getNumberOfTriggers)
				.def("getTrigger", &Navigation::getTrigger)
				.def("getNumberOfSpawnPoints", &Navigation::getNumberOfSpawnPoints)
				.def("getSpawnPoint", &Navigation::getSpawnPoint)
				.def("getNumberOfPoints", &Navigation::getNumberOfPoints)
				,
				class_<ULuaAgent>("LuaAgent")
				.def("randomDouble", &ULuaAgent::randomDouble)
				.def("selectWeapon", &ULuaAgent::selectWeapon)
				.def("moveDirection", &ULuaAgent::moveDirection)
				.def("moveTo", &ULuaAgent::moveTo)
				.def("reload", &ULuaAgent::reload)
				.def("rotate", &ULuaAgent::rotate)
				.def("shootAt", &ULuaAgent::shootAt)
				.def("shootAtPoint", &ULuaAgent::shootAtPoint)
				.def("wait", &ULuaAgent::wait)
				.def("continueAction", &ULuaAgent::continueAction)
				.def("printMessage", &ULuaAgent::printMessage)
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
	AEvaGameState *game = GetWorld()->GetGameState<AEvaGameState>();
	lua_State *pL = game->GetLuaContextFor(GetControlledCharacter());
		// ULuaAgent::createLuaEnv();

	std::string name(TCHAR_TO_UTF8(*filename));

	int error = luaL_loadfile(pL, name.c_str()) || lua_pcall(pL, 0, LUA_MULTRET, 0);
	if (error) {
		std::ostringstream err_stream;
		err_stream << "[Lua] Error " << error << ": " << lua_tostring(pL, -1) << " - during execution of script: " << name << "\n";
		FString err(err_stream.str().c_str());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, err);
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
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Executing function: " + wtn);

	// Call the function in the lua script.
	try {
		ActorKnowledge *ak = GetControlledCharacter()->getActorKnowledge();
		float t = GetWorld()->GetGameState<AEvaGameState>()->GetFloatTimeInSeconds();
		call_function<void>(luaEnv,	whatToName.c_str(),	this, ak, t);
	}
	catch (...) {
		FString fug(lua_tostring(luaEnv, -1));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, fug);
	}
}

void ULuaAgent::onStart()
{
	FString osn(UTF8_TO_TCHAR(onStartName.c_str()));
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Executing function: " + osn);

	// Call the function in the lua script.
	try {
		ActorKnowledge *ak = GetControlledCharacter()->getActorKnowledge();
		float t = GetWorld()->GetGameState<AEvaGameState>()->GetFloatTimeInSeconds();
		call_function<void>(luaEnv, onStartName.c_str(), this, ak, t);
	}
	catch (...) {
		FString fug(lua_tostring(luaEnv, -1));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, fug);
	}
}

double ULuaAgent::randomDouble()
{
	return FMath::FRand();
}

void ULuaAgent::selectWeapon(EWeaponType weapon)
{
	if ((int)weapon < 0 || (int)weapon > 3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "selectWeapon: attempted to select out of range");
		return;
	}
	GetControlledCharacter()->selectWeapon(weapon);
}

void ULuaAgent::moveDirection(Vector4d direction)
{
	FVector DirectionFV(direction.val[0], direction.val[1], direction.val[2]);
	GetControlledCharacter()->moveDirection(DirectionFV);
}

void ULuaAgent::moveTo(Vector4d target)
{
	FVector TargetFV(target.val[0], target.val[1], target.val[2]);
	GetControlledCharacter()->moveTo(TargetFV);
}

void ULuaAgent::reload()
{
	GetControlledCharacter()->reload();
}

void ULuaAgent::rotate(Vector4d direction)
{
	FVector RotationFV(direction.val[0], direction.val[1], direction.val[2]);
	FRotator Rotator = RotationFV.Rotation();
	GetControlledCharacter()->rotate(Rotator);
}

void ULuaAgent::shootAt(ActorInfo enemy)
{
	shootAtPoint(enemy.getPosition()); // TODO maybe use EvaCharacter::shootAt?
}

void ULuaAgent::shootAtPoint(Vector4d vect)
{
	FVector ShootFV(vect.val[0], vect.val[1], vect.val[2]);
	GetControlledCharacter()->shootAtPoint(ShootFV);
}

void ULuaAgent::wait()
{
	GetControlledCharacter()->wait();
}

void ULuaAgent::continueAction()
{
	GetControlledCharacter()->continueAction();
}

void ULuaAgent::printMessage(const char* msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, msg);
}