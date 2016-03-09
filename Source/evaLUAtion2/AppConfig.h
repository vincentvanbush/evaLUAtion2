// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AppConfig.generated.h"

/**
 * 
 */
UCLASS()
class EVALUATION2_API UAppConfig : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "AppConfig")
	static bool GetGameIniStr(FString sec, FString key, FString &recv)
	{
		return GConfig && GConfig->GetString(
			*sec,
			*key,
			recv,
			GGameIni
		);
	}

	UFUNCTION(BlueprintCallable, Category = "AppConfig")
	static bool GetGameIniBool(FString sec, FString key, bool &recv)
	{
		return GConfig && GConfig->GetBool(
			*sec,
			*key,
			recv,
			GGameIni
		);
	}

	UFUNCTION(BlueprintCallable, Category = "AppConfig")
	static bool GetGameIniInt(FString sec, FString key, int32 &recv)
	{
		return GConfig && GConfig->GetInt(
			*sec,
			*key,
			recv,
			GGameIni
		);
	}

	UFUNCTION(BlueprintCallable, Category = "AppConfig")
	static bool GetGameIniFloat(FString sec, FString key, float &recv)
	{
		return GConfig && GConfig->GetFloat(
			*sec,
			*key,
			recv,
			GGameIni
		);
	}

	UFUNCTION(BlueprintCallable, Category = "AppConfig")
	static void SetGameIniStr(FString sec, FString key, FString val)
	{
		GConfig->SetString(*sec, *key, *val, GGameIni);
		GConfig->Flush(false, GGameIni);
	}
	
	UFUNCTION(BlueprintCallable, Category = "AppConfig")
	static void SetGameIniBool(FString sec, FString key, bool val)
	{
		GConfig->SetBool(*sec, *key, val, GGameIni);
		GConfig->Flush(false, GGameIni);
	}
	
	UFUNCTION(BlueprintCallable, Category = "AppConfig")
	static void SetGameIniInt(FString sec, FString key, int32 val)
	{
		GConfig->SetInt(*sec, *key, val, GGameIni);
		GConfig->Flush(false, GGameIni);
	}
	
	UFUNCTION(BlueprintCallable, Category = "AppConfig")
	static void SetGameIniFloat(FString sec, FString key, float val)
	{
		GConfig->SetFloat(*sec, *key, val, GGameIni);
		GConfig->Flush(false, GGameIni);
	}


	
};
