// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include <boost/program_options.hpp>
#include "Configuration.generated.h"

/**
 * 
 */
UCLASS()
class EVALUATION2_API UConfiguration : public UObject
{
	GENERATED_BODY()
	
public:

	UConfiguration(const FObjectInitializer &ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = Config)
		void LoadOptionsFromFile(FString filename);

	UFUNCTION(BlueprintCallable, Category = Config)
		bool GetBool(FString opt);

	UFUNCTION(BlueprintCallable, Category = Config)
		int32 GetInt(FString opt);

	UFUNCTION(BlueprintCallable, Category = Config)
		float GetFloat(FString opt);

	UFUNCTION(BlueprintCallable, Category = Config)
		FString GetString(FString opt);

	UFUNCTION(BlueprintCallable, Category = Config)
		bool IsSet(FString opt);

	static UConfiguration* RetrieveFromGameState();

private:

	boost::program_options::variables_map vm;
	boost::program_options::options_description cmdline_options;
	boost::program_options::options_description config_file_options;
	
};
