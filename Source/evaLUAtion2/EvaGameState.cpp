// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "LuaAgent.h"
#include <boost/program_options.hpp>
#include <fstream>
#include <string>
#include "EvaGameState.h"

using namespace boost::program_options;

lua_State* AEvaGameState::GetLuaContextFor(AEvaCharacter *character)
{
	int32 team = character->team;
	std::map<int32, lua_State*>::const_iterator it = TeamLuaContexts.find(team);
	if (it == TeamLuaContexts.end())
	{
		return TeamLuaContexts[team] = ULuaAgent::createLuaEnv();
	}
	return it->second;
}

AEvaGameState::AEvaGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Configuration = NewObject<UConfiguration>();

	/*
	*	Initialize constant arrays
	*/
	const bool stopAtTargetInit[EWeaponType::WeaponSize] = { false, false, true, false };
	const int32 numberOfParticlesInit[EWeaponType::WeaponSize] = { 1, 1, 1, 10 };
	const float arcInit[EWeaponType::WeaponSize] = { 0.7, 0.1, 0.3, 3.0 };
	const int32 ammoPacksInit[EWeaponType::WeaponSize] = { 100, 5, 10, 15 };
	const float radiusInit[EWeaponType::WeaponSize] = { 0, 0, 50, 0 };
	const int32 reloadTimeInit[EWeaponType::WeaponSize] = { 0, 3, 1.5, 1 };
	const float damageInit[EWeaponType::WeaponSize] = { 5, 100, 50, 15 };
	const int32 colorInit[EWeaponType::WeaponSize] = { 0x00FF00FF, 0x0000FFFF, 0xFF0000FF, 0x000000FF };
	const float speedInit[EWeaponType::WeaponSize] = { 500, 15000, 350, 1000 };
	const int32 shootTimeInit[EWeaponType::WeaponSize] = { 1, 5, 1.5, 1 };

	stopAtTarget.Append(stopAtTargetInit, ARRAY_COUNT(stopAtTargetInit));
	numberOfParticles.Append(numberOfParticlesInit, ARRAY_COUNT(numberOfParticlesInit));
	arc.Append(arcInit, ARRAY_COUNT(arcInit));
	ammoPacks.Append(ammoPacksInit, ARRAY_COUNT(ammoPacksInit));
	radius.Append(radiusInit, ARRAY_COUNT(radiusInit));
	reloadTime.Append(reloadTimeInit, ARRAY_COUNT(reloadTimeInit));
	damage.Append(damageInit, ARRAY_COUNT(damageInit));
	color.Append(colorInit, ARRAY_COUNT(colorInit));
	speed.Append(speedInit, ARRAY_COUNT(speedInit));
	shootTime.Append(shootTimeInit, ARRAY_COUNT(shootTimeInit));
}

void AEvaGameState::StartGame(FString CfgFile)
{
	// tak z grubsza:
	
	// za³adowanie zawartoœci pliku konfiguracyjnego i ustawienie opcji gry
	Configuration->LoadOptionsFromFile(CfgFile);

	// za³adowanie danych o aktorach
		// w tym: dla ka¿dego z nich za³adowanie w³aœciwego skryptu

	// spawnowanie obiektów i postaci przez GetWorld()->SpawnActor(...)

	// wyczyszczenie tablic i dodanie do nich wszystkiego co mamy :)
}
