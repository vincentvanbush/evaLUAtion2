// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "Action.h"
#include "PlayerAgent.h"


UAction* UPlayerAgent::decideNextAction(){ return nullptr; };			//corresponds to whatToDoNow method

void UPlayerAgent::selectWeapon(EWeaponType weapon){};

void UPlayerAgent::moveDirection(FVector direction){};

void UPlayerAgent::moveTo(FVector target){};

void UPlayerAgent::reload(){};

void UPlayerAgent::rotate(FVector direction){};

void UPlayerAgent::shootAt(AEvaCharacter* enemy){};

void UPlayerAgent::shootAtPoint(FVector vect){};

void UPlayerAgent::wait(){};

void UPlayerAgent::continueAction(){};


