// Fill out your copyright notice in the Description page of Project Settings.

#include "evaLUAtion2.h"
#include "Configuration.h"
#include "EvaGameState.h"
#include <fstream>

using namespace boost::program_options;

UConfiguration *UConfiguration::RetrieveFromGameState()
{
	return GEngine->GetWorld()->GetGameState<AEvaGameState>()->Configuration;
}

UConfiguration::UConfiguration(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	options_description generic("Generic options");
	generic.add_options()
		("height,h", value<int>()->default_value(600), "window height")
		("width,w", value<int>()->default_value(800), "window width")
		("map.actors.file", value<std::string>()->default_value("actors.eaf"), "file with actors definition")
		("map.filename", value<std::string>()->default_value("random"), "map to use")
		("respawns", value<int>()->default_value(1), "do agents respawn")
		;

	options_description config("Configuration file options");
	config.add_options()
		("actor.speed", value<double>()->default_value(10.0))
		("actor.maxHealth", value<int>()->default_value(100))
		("actor.maxArmour", value<int>()->default_value(100))
		("weapon.chaingun.ammo", value<int>()->default_value(50))
		("weapon.railgun.ammo", value<int>()->default_value(3))
		("weapon.rocket.ammo", value<int>()->default_value(5))
		("weapon.shotgun.ammo", value<int>()->default_value(4))
		("trigger.addHealth", value<int>()->default_value(25))
		("graphics.showHealthNumber", value<int>()->default_value(0))
		("graphics.showHealthBar", value<int>()->default_value(1))
		;

	options_description command("Command line options");
	command.add_options()
		("config-file", value<std::string>()->default_value("evaLUAtion.cfg"), "configuration file")
		;

	cmdline_options.add(generic).add(command);
	config_file_options.add(generic).add(config);
}

void UConfiguration::LoadOptionsFromFile(FString filename)
{
	std::string stdFileName(TCHAR_TO_UTF8(*filename));
	std::ifstream ifs(stdFileName.c_str());
	store(parse_config_file(ifs, config_file_options), vm);
	notify(vm);
}

bool UConfiguration::GetBool(FString opt)
{
	return (GetInt(opt) != 0);
}

//int32 UConfiguration::GetInt(FString opt)
//{
//	float x = GetFloat(opt);
//	return x;
//}

int32 UConfiguration::GetInt(FString opt)
{
	std::string optionName(TCHAR_TO_UTF8(*opt));
	boost::any::holder<int>* holder = static_cast<boost::any::holder<int>* >(vm[optionName].value().content);
	if (holder)
	{
		return holder->held;
	}
	else
	{
		return 0;
	}
}

float UConfiguration::GetFloat(FString opt)
{
	std::string optionName(TCHAR_TO_UTF8(*opt));
	boost::any::holder<double>* holder = static_cast<boost::any::holder<double>* >(vm[optionName].value().content);
	if (holder)
	{
		return holder->held;
	}
	else
	{
		return 0;
	}
}

FString UConfiguration::GetString(FString opt)
{
	std::string optionName(TCHAR_TO_UTF8(*opt));

	boost::any::holder<double>* holder = dynamic_cast<boost::any::holder<double>* >(vm[optionName].value().content);

	if (holder)
	{
		return FString(boost::lexical_cast<std::string>(holder->held).c_str());
	}
	else
	{
		boost::any::holder<std::string>* holder = static_cast<boost::any::holder<std::string>* >(vm[optionName].value().content);
		if (holder)
		{
			return UTF8_TO_TCHAR(holder->held.c_str());
		}
		else
		{
			return FString("ERROR");
		}
	}
}

bool UConfiguration::IsSet(FString opt)
{
	std::string optionName(TCHAR_TO_UTF8(*opt));
	return (vm.count(optionName) > 0);
}