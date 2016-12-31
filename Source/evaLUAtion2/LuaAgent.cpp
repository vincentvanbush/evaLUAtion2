// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "LuaAgent.h"
#include <iostream>
#include <sstream>
#include <LuaBridge.h>
#include "EvaGameState.h"

extern "C" {
	#include "Lib/Lua-5.3.3/include/lua.h"
	#include "Lib/Lua-5.3.3/include/lualib.h"
	#include "Lib/Lua-5.3.3/include/lauxlib.h"
}

#include "Misc.h"
#include <vector>
//#include "ActorInfo.h"
#include "ActorKnowledge.h"
#include "Navigation.h"

typedef std::vector<ActorInfo>::reference(std::vector<ActorInfo>:: *AtFunctionType)(std::vector<ActorInfo>::size_type);
typedef std::vector<ActorInfo>::size_type(std::vector<ActorInfo>:: *SizeFunctionType)();

lua_State * ULuaAgent::createLuaEnv() {
	lua_State * pL = luaL_newstate();
	luaL_openlibs(pL);
	luabridge::getGlobalNamespace(pL)
		.beginClass<ActorInfoVectorWrapper>("vectorOfActorInfo")
			.addFunction("size", &ActorInfoVectorWrapper::size)
			.addFunction("at", &ActorInfoVectorWrapper::at)
		.endClass()
		.beginClass<IntVectorWrapper>("vectorOfInt")
			.addFunction("size", &IntVectorWrapper::size)
			.addFunction("at", &IntVectorWrapper::at)
		.endClass()
		.beginClass<ActorInfo>("ActorInfo")
			.addConstructor<void(*)()>()
			.addFunction("getHealth", &ActorInfo::getHealth)
			.addFunction("getPosition", &ActorInfo::getPosition)
			.addFunction("getDirection", &ActorInfo::getDirection)
			.addFunction("getTeam", &ActorInfo::getTeam)
			.addFunction("getName", &ActorInfo::getName)
			.addFunction("getWeaponType", &ActorInfo::getWeaponType)
			.addFunction("setHealth", &ActorInfo::setHealth)
			.addFunction("setPosition", &ActorInfo::setPosition)
			.addFunction("setDirection", &ActorInfo::setDirection)
			.addFunction("setTeam", &ActorInfo::setTeam)
			.addFunction("setWeaponType", &ActorInfo::setWeaponType)
		.endClass()
		// TODO uncomment when ready
		.beginClass<ActorKnowledge>("ActorKnowledge")
			.addFunction("getActionType", &ActorKnowledge::getActionType)
			.addFunction("getName", &ActorKnowledge::getName)
			.addFunction("getPosition", &ActorKnowledge::getPosition)
			.addFunction("getDirection", &ActorKnowledge::getDirection)
			.addFunction("getTeam", &ActorKnowledge::getTeam)
			.addFunction("getWeaponType", &ActorKnowledge::getWeaponType)
			.addFunction("getHealth", &ActorKnowledge::getHealth)
			.addFunction("getAmmo", &ActorKnowledge::getAmmo)
			.addFunction("getSeenActors", &ActorKnowledge::getSeenActors)
			.addFunction("getSeenFriends", &ActorKnowledge::getSeenFriends)
			.addFunction("getSeenFoes", &ActorKnowledge::getSeenFoes)
			.addFunction("getEstimatedTimeToReach", &ActorKnowledge::getEstimatedTimeToReach)
			.addFunction("getSelf", &ActorKnowledge::getSelf)
			.addFunction("getNavigation", &ActorKnowledge::getNavigation)
			.addFunction("getArmour", &ActorKnowledge::getArmour)
			.addFunction("isMoving", &ActorKnowledge::isMoving)
			.addFunction("isLoaded", &ActorKnowledge::isLoaded)
			.addFunction("getLongDestination", &ActorKnowledge::getLongDestination)
			.addFunction("getShortDestination", &ActorKnowledge::getShortDestination)
			.addStaticProperty("Chaingun", &ActorKnowledge::chaingun)
			.addStaticProperty("Railgun", &ActorKnowledge::railgun)
			.addStaticProperty("RocketLauncher", &ActorKnowledge::rocketlauncher)
			.addStaticProperty("Shotgun", &ActorKnowledge::shotgun)
			.addStaticProperty("WeaponSize", &ActorKnowledge::weaponsize)
			.addStaticProperty("Moving", &ActorKnowledge::moving)
			.addStaticProperty("Shootinh", &ActorKnowledge::shooting)
			.addStaticProperty("ChangingWeapon", &ActorKnowledge::changingweapon)
			.addStaticProperty("Dying", &ActorKnowledge::dying)
			.addStaticProperty("Reloading", &ActorKnowledge::reloading)
			.addStaticProperty("Waiting", &ActorKnowledge::waiting)
		.endClass()
		.beginClass<Trigger>("Trigger")
			.addStaticProperty("Weapon", &Trigger::weapon)
			.addStaticProperty("Armour", &Trigger::armour)
			.addStaticProperty("Health", &Trigger::health)
			.addFunction("getType", &Trigger::getType)
			.addFunction("isActive", &Trigger::isActive)
			.addFunction("getPosition", &Trigger::getPosition)
			.addFunction("getBoundingRadius", &Trigger::getBoundingRadius)
		.endClass()
		.beginClass<Navigation>("Navigation")
			.addFunction("anyRayCrateColision", &Navigation::anyRayCrateColision)
			.addFunction("getNodePosition", &Navigation::getNodePosition)
			//.addFunction("searchWay", (std::vector<int>(Navigation:: *)(Vector4d, Vector4d)) &Navigation::searchWay)
			.addFunction("getNumberOfTriggers", &Navigation::getNumberOfTriggers)
			.addFunction("getTrigger", &Navigation::getTrigger)
			.addFunction("getNumberOfSpawnPoints", &Navigation::getNumberOfSpawnPoints)
			.addFunction("getSpawnPoint", &Navigation::getSpawnPoint)
			.addFunction("getNumberOfPoints", &Navigation::getNumberOfPoints)
		.endClass()
		.beginClass<ULuaAgent>("LuaAgent")
			.addFunction("randomDouble", &ULuaAgent::randomDouble)
			.addFunction("selectWeapon", &ULuaAgent::selectWeapon)
			.addFunction("moveDirection", &ULuaAgent::moveDirection)
			.addFunction("moveTo", &ULuaAgent::moveTo)
			.addFunction("reload", &ULuaAgent::reload)
			.addFunction("rotate", &ULuaAgent::rotate)
			.addFunction("shootAt", &ULuaAgent::shootAt)
			.addFunction("shootAtPoint", &ULuaAgent::shootAtPoint)
			.addFunction("wait", &ULuaAgent::wait)
			.addFunction("continueAction", &ULuaAgent::continueAction)
			.addFunction("printMessage", &ULuaAgent::printMessage)
		.endClass()
		.beginClass<Vector4d>("Vector4d")
			.addFunction("value", &Vector4d::value)
			.addConstructor<void(*)(double, double, double, double)>()
			.addFunction("dot", &Vector4d::dot)
			.addFunction("length", &Vector4d::length)
			.addFunction("lengthSquared", &Vector4d::lengthSquared)
			.addFunction("normal", &Vector4d::normal)
			.addFunction("normalize", &Vector4d::normalize)
			.addFunction("__mul", &Vector4d::operator*)
			.addFunction("__div", &Vector4d::operator/)
			.addFunction("__add", &Vector4d::operator+)
			.addFunction("__sub", &Vector4d::operator-)
			.addFunction("__eq", &Vector4d::operator==)
		.endClass()
	.endNamespace();
	/*open(pL);
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
				.addFunction("size", &ActorInfoVectorWrapper::size)
				.addFunction("at", &ActorInfoVectorWrapper::at)
				,
				class_<IntVectorWrapper >("vectorOfInt")
				.addFunction("size", &IntVectorWrapper::size)
				.addFunction("at", &IntVectorWrapper::at)
				,
				class_<ActorInfo>("ActorInfo")
				.addFunction(constructor<>())

				.addFunction("getHealth", &ActorInfo::getHealth)
				.addFunction("getPosition", &ActorInfo::getPosition)
				.addFunction("getDirection", &ActorInfo::getDirection)
				.addFunction("getTeam", &ActorInfo::getTeam)
				.addFunction("getName", &ActorInfo::getName)
				.addFunction("getWeaponType", &ActorInfo::getWeaponType)
				.addFunction("setHealth", &ActorInfo::setHealth)
				.addFunction("setPosition", &ActorInfo::setPosition)
				.addFunction("setDirection", &ActorInfo::setDirection)
				.addFunction("setTeam", &ActorInfo::setTeam)
				.addFunction("setWeaponType", &ActorInfo::setWeaponType)
				,
				// TODO uncomment when ready
				class_<ActorKnowledge>("ActorKnowledge")
				.addFunction("getActionType", &ActorKnowledge::getActionType)
				.addFunction("getName", &ActorKnowledge::getName)
				.addFunction("getPosition", &ActorKnowledge::getPosition)
				.addFunction("getDirection", &ActorKnowledge::getDirection)
				.addFunction("getTeam", &ActorKnowledge::getTeam)
				.addFunction("getWeaponType", &ActorKnowledge::getWeaponType)
				.addFunction("getHealth", &ActorKnowledge::getHealth)
				.addFunction("getAmmo", &ActorKnowledge::getAmmo)
				.addFunction("getSeenActors", &ActorKnowledge::getSeenActors)
				.addFunction("getSeenFriends", &ActorKnowledge::getSeenFriends)
				.addFunction("getSeenFoes", &ActorKnowledge::getSeenFoes)
				.addFunction("getEstimatedTimeToReach", &ActorKnowledge::getEstimatedTimeToReach)
				.addFunction("getSelf", &ActorKnowledge::getSelf)
				.addFunction("getNavigation", &ActorKnowledge::getNavigation)
				.addFunction("getArmour", &ActorKnowledge::getArmour)
				.addFunction("isMoving", &ActorKnowledge::isMoving)
				.addFunction("isLoaded", &ActorKnowledge::isLoaded)
				.addFunction("getLongDestination", &ActorKnowledge::getLongDestination)
				.addFunction("getShortDestination", &ActorKnowledge::getShortDestination)
				,
				class_<Trigger>("Trigger")
				.enum_("TriggerType")
				[
					value("Weapon", 0),
					value("Armour", 1),
					value("Health", 2)
				]
			.addFunction("getType", &Trigger::getType)
				.addFunction("isActive", &Trigger::isActive)
				.addFunction("getPosition", &Trigger::getPosition)
				.addFunction("getBoundingRadius", &Trigger::getBoundingRadius)
				,
				class_<Navigation>("Navigation")
				.addFunction("anyRayCrateColision", &Navigation::anyRayCrateColision)
				.addFunction("getNodePosition", &Navigation::getNodePosition)
				//.addFunction("searchWay", (std::vector<int>(Navigation:: *)(Vector4d, Vector4d)) &Navigation::searchWay)
				.addFunction("getNumberOfTriggers", &Navigation::getNumberOfTriggers)
				.addFunction("getTrigger", &Navigation::getTrigger)
				.addFunction("getNumberOfSpawnPoints", &Navigation::getNumberOfSpawnPoints)
				.addFunction("getSpawnPoint", &Navigation::getSpawnPoint)
				.addFunction("getNumberOfPoints", &Navigation::getNumberOfPoints)
				,
				class_<ULuaAgent>("LuaAgent")
				.addFunction("randomDouble", &ULuaAgent::randomDouble)
				.addFunction("selectWeapon", &ULuaAgent::selectWeapon)
				.addFunction("moveDirection", &ULuaAgent::moveDirection)
				.addFunction("moveTo", &ULuaAgent::moveTo)
				.addFunction("reload", &ULuaAgent::reload)
				.addFunction("rotate", &ULuaAgent::rotate)
				.addFunction("shootAt", &ULuaAgent::shootAt)
				.addFunction("shootAtPoint", &ULuaAgent::shootAtPoint)
				.addFunction("wait", &ULuaAgent::wait)
				.addFunction("continueAction", &ULuaAgent::continueAction)
				.addFunction("printMessage", &ULuaAgent::printMessage)
				,
				class_<Vector4d>("Vector4d")
				.addFunction("value", &Vector4d::value)
				.addFunction(constructor<double, double, double, double>())
				.addFunction("dot", &Vector4d::dot)
				.addFunction("length", &Vector4d::length)
				.addFunction("lengthSquared", &Vector4d::lengthSquared)
				.addFunction("normal", &Vector4d::normal)
				.addFunction("normalize", &Vector4d::normalize)
				.addFunction(self * double())
				.addFunction(self / double())
				.addFunction(self + other<Vector4d>())
				.addFunction(self - other<Vector4d>())
				.addFunction(self == other<Vector4d>())
		];*/
	return pL;
}

AEvaCharacter* ULuaAgent::GetControlledCharacter()
{
	return Cast<AEvaCharacter>(GetOwner());
}

ULuaAgent::~ULuaAgent()
{
	if (whatToHandle) {
		delete whatToHandle;
		whatToHandle = NULL;
	}
	if (onStartHandle) {
		delete onStartHandle;
		onStartHandle = NULL;
	}
}

void ULuaAgent::Initialize(FString filename)
{
	AEvaGameState *game = GetWorld()->GetGameState<AEvaGameState>();
	lua_State *pL = game->GetLuaContextFor(GetControlledCharacter());
		// ULuaAgent::createLuaEnv();

	std::string name(TCHAR_TO_UTF8(*filename));

	int error = luaL_dofile(pL, name.c_str());
	if (error) {
		std::ostringstream err_stream;
		err_stream << "[Lua] Error " << error << ": " << lua_tostring(pL, -1) << " - during loading of script: " << name << "\n";
		FString err(err_stream.str().c_str());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, err);
	}

	this->luaEnv = pL;
	
	name.resize(name.length() - 4);

	FString baseName = FPaths::GetBaseFilename(filename);
	std::string stdBaseName(TCHAR_TO_UTF8(*baseName));
	whatToName = std::string(stdBaseName + "whatTo");
	onStartName = std::string(stdBaseName + "onStart");
	whatToHandle = new luabridge::LuaRef(luaEnv);
	(*whatToHandle) = luabridge::getGlobal(luaEnv, whatToName.c_str());
	onStartHandle = new luabridge::LuaRef(luaEnv);
	(*onStartHandle) = luabridge::getGlobal(luaEnv, onStartName.c_str());
}

void ULuaAgent::whatToDo()
{
	FString wtn(UTF8_TO_TCHAR(whatToName.c_str()));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Executing function: " + wtn);

	// Call the function in the lua script.
	try {
		ActorKnowledge *ak = GetControlledCharacter()->getActorKnowledge();
		float t = GetWorld()->GetGameState<AEvaGameState>()->GetFloatTimeInSeconds();
		(*whatToHandle)(this, ak, t);
	}
	catch (...) {
		FString fug(lua_tostring(luaEnv, -1));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, fug);
	}
}

void ULuaAgent::onStart()
{
	FString osn(UTF8_TO_TCHAR(onStartName.c_str()));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Executing function: " + osn);

	// Call the function in the lua script.
	try {
		ActorKnowledge *ak = GetControlledCharacter()->getActorKnowledge();
		float t = GetWorld()->GetGameState<AEvaGameState>()->GetFloatTimeInSeconds();
		(*onStartHandle)(this, ak, t);
		
		//call_function<void>(luaEnv, onStartName.c_str(), this, ak, t);
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

void ULuaAgent::selectWeapon(int weapon)
{
	if (weapon < 0 || weapon > 3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "selectWeapon: attempted to select out of range");
		return;
	}
	uint32 type = (uint32)weapon;
	GetControlledCharacter()->selectWeapon(type);
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