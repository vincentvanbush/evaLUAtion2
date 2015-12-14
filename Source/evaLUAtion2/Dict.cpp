// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "Dict.h"

FString UDict::GetItem(FString key)
{
	return _map[key];
}

void UDict::SetItem(FString key, FString val)
{
	_map.Add(key, val);
}