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
