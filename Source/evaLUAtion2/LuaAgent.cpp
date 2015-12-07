// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "LuaAgent.h"

AEvaCharacter* ULuaAgent::GetControlledCharacter()
{
	return Cast<AEvaCharacter>(GetOwner());
}

void ULuaAgent::Initialize(FString &filename)
{
	
}

void ULuaAgent::whatToDo()
{
	
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
