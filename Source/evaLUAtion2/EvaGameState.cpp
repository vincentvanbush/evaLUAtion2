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