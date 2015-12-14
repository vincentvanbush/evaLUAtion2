// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "LuaAgent.h"
#include "EvaGameState.h"

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
	Settings = NewObject<UDict>();
}

void AEvaGameState::StartGame(FString ActorsFile, FString CfgFile)
{
	// tak z grubsza:

	// za³adowanie danych o aktorach
		// w tym: dla ka¿dego z nich za³adowanie w³aœciwego skryptu

	// spawnowanie obiektów i postaci przez GetWorld()->SpawnActor(...)
	
	// za³adowanie zawartoœci pliku konfiguracyjnego i ustawienie opcji gry

	// wyczyszczenie tablic i dodanie do nich wszystkiego co mamy :)
}