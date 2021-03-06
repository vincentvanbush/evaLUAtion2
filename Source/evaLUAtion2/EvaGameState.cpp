// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "LuaAgent.h"
#include <boost/program_options.hpp>
#include <fstream>
#include <set>
#include <string>
#include "EvaGameState.h"

using namespace boost::program_options;
using namespace std;

void AEvaGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GameHasEnded && GameFinished())
	{
		GameHasEnded = true;
		OnGameEnd.Broadcast();
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Ebin :D"); // call the event dispatcher here
	}
}

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
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

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

bool AEvaGameState::StartGame(
	FString CfgFile,
	TArray<FNewCharacterInfo> &CharactersInfo,
	FString &MapFile
)
{
	TeamLuaContexts.clear();
	GameStartedAt = GetWorld()->GetTimeSeconds();
	/*std::string a(TCHAR_TO_UTF8(*CfgFile));*/
	FString ProfileFolderPath;
	FString CfgFilename;
	FString ProfilesFolderPath;
	FString MainPath;
	FString Temp;
	if (!CfgFile.Split(TEXT("/"), &ProfileFolderPath, &CfgFilename, ESearchCase::IgnoreCase, ESearchDir::FromEnd))
		return false;
	// za�adowanie zawarto�ci pliku konfiguracyjnego i ustawienie opcji gry
	Configuration = NewObject<UConfiguration>();
	Configuration->LoadOptionsFromFile(CfgFile);
	FString EmfFilename = Configuration->GetString("map.filename");
	FString EafFilename = Configuration->GetString("map.actors.file");

	FString EafFile = ProfileFolderPath + "/" + EafFilename;

	MapFile = EmfFilename;

	if (!LoadActorsFile(EafFile, ProfileFolderPath, CharactersInfo))
		return false;


	// za�adowanie danych o aktorach
		// w tym: dla ka�dego z nich za�adowanie w�a�ciwego skryptu

	// spawnowanie obiekt�w i postaci przez GetWorld()->SpawnActor(...)

	// wyczyszczenie tablic i dodanie do nich wszystkiego co mamy :)
	return true;
}

bool AEvaGameState::GameFinished_Implementation()
{
	if (Characters.Num() == 0) return false;

	bool respawnsEnabled = Configuration->GetBool("respawns");
	
	// Respawns enabled - compare the current timer value with the specified game time.
	if (respawnsEnabled)
	{
		int matchTime = Configuration->GetInt("matchtime");
		if (GetFloatTimeInSeconds() >= matchTime) return true;
		return false;
	}

	// No respawns - count teams:
	std::set<int> teamNumbers;
	bool alreadyFoundAliveTeam = false;
	for (auto it = Characters.CreateIterator(); it; it++)
	{
		auto character = *it;
		teamNumbers.insert(character->team);
	}
	auto alive = Characters.FilterByPredicate([](AEvaCharacter *character){ return !character->IsDead(); });

	// No sense declaring the game finished just if there's only one team.
	// Check if there's only one or no character left in that case.
	if (teamNumbers.size() < 2)
	{
		if (alive.Num() < 2) return true;
		return false;
	}
		
	for (auto it = teamNumbers.begin(); it != teamNumbers.end(); it++)
	{
		bool teamAlive = alive.ContainsByPredicate([&](AEvaCharacter *character){ return character->team == *it; });
		if (teamAlive)
		{
			if (alreadyFoundAliveTeam) return false;
			else alreadyFoundAliveTeam = true;
		}
	}
	return true;
}

void AEvaGameState::Clear_Implementation()
{
	for (auto it = Powerups.CreateIterator(); it; it++)
	{
		auto x = *it;
		x->Destroy();
	}
	Powerups.Empty();
	for (auto it = Waypoints.CreateIterator(); it; it++)
	{
		auto x = *it;
		x->Destroy();
	}
	Waypoints.Empty();
	for (auto it = Spawnpoints.CreateIterator(); it; it++)
	{
		auto x = *it;
		x->Destroy();
	}
	Spawnpoints.Empty();
	for (auto it = Walls.CreateIterator(); it; it++)
	{
		auto x = *it;
		x->Destroy();
	}
	Walls.Empty();
	for (auto it = Characters.CreateIterator(); it; it++)
	{
		auto x = *it;
		x->Destroy();
	}
	Characters.Empty();
	GameHasEnded = false;
}

bool AEvaGameState::LoadActorsFile(
	FString FileName,
	FString ParentFolderPath,
	TArray<FNewCharacterInfo> &CharactersInfo
	)
{
	FString LoadDirectory = FileName;
	FString loaded;

	if (!FFileHelper::LoadFileToString(loaded, *LoadDirectory))
		return false;

	string LoadedText(TCHAR_TO_UTF8(*loaded));

	stringstream ss(stringstream::in | stringstream::out);
	ss << LoadedText;


	const int BUFFSIZE = 256;
	char buff[BUFFSIZE];
	stringstream line(stringstream::in | stringstream::out);

	string ActorName;
	string Script;
	int Team;
	int Position[2];

	FNewCharacterInfo CharacterInfo;
	FString ProfilesFolderPath;
	FString MainPath;
	FString Temp;

	while (ss.getline(buff, BUFFSIZE)) {
		line << buff;
		line >> ActorName >> Script >> Team >> Position[0] >> Position[1];

		CharacterInfo.CharacterName = FString(ActorName.c_str());
		if (Script.compare(0, 2, "ms") == 0) {
			CharacterInfo.ScriptFile = FString();
		}
		else if (Script.compare(0, 3, "sc:") == 0) {
			if (!ParentFolderPath.Split(TEXT("/"), &ProfilesFolderPath, &Temp, ESearchCase::IgnoreCase, ESearchDir::FromEnd))
				return false;
			if (!ProfilesFolderPath.Split(TEXT("/"), &MainPath, &Temp, ESearchCase::IgnoreCase, ESearchDir::FromEnd))
				return false;
			
			CharacterInfo.ScriptFile = MainPath + "/Scripts/" + FString(Script.substr(3).c_str());
		}
		else {
			// case when invalid file
		}
		CharacterInfo.Team = Team;
		CharacterInfo.Position = FVector2D((float)Position[0], (float)Position[1]);
		CharactersInfo.Add(CharacterInfo);
	}
	return true;
}

float AEvaGameState::GetFloatTimeInSeconds_Implementation()
{
	return GetWorld()->GetTimeSeconds() - GameStartedAt;
}