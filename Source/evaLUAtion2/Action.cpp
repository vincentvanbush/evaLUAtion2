// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "EvaCharacter.h"
#include "Action.h"


//function called unconditionally everytime an action is called
void UAction::OnEnter_Implementation()
{
	ActionStarted = GetWorld()->GetTimeSeconds();
}
