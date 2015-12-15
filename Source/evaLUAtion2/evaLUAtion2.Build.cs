// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;

public class evaLUAtion2 : ModuleRules
{
	public evaLUAtion2(TargetInfo Target)
	{
	    bUseRTTI = true;

	    string evaLUAtionDir = ModuleDirectory;

        // bEnableExceptions = true;

        string LuaPath = "D:/work/lib/lua5_1_3_Win32_dll8_lib";
	    string LuabindPath = "D:/work/lib/luabind-0.9.1";
	    string BoostPath = "D:/work/lib/boost_1_55_0_64";

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[] {
            evaLUAtionDir,
            Path.Combine(LuaPath, "include"),
            LuabindPath,
            BoostPath
        });

        PublicAdditionalLibraries.Add("D:/work/lib/lua5_1_3_Win32_dll8_lib/lua5.1.3_64.lib");
        // PublicAdditionalLibraries.Add("D:/work/lib/lua5_1_3_Win32_dll8_lib/lua51.lib");

	    PublicAdditionalLibraries.Add("D:/work/lib/luabind-0.9.1/lib/Luabind64.lib");

	    string BoostLibPath = Path.Combine(BoostPath, "lib64-msvc-12.0");

        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_atomic-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_bzip2-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_chrono-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_context-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_coroutine-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_date_time-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_exception-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_filesystem-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_graph-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_iostreams-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_locale-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_log_setup-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_log-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_c99f-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_c99l-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_c99-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_tr1f-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_tr1l-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_tr1-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_prg_exec_monitor-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_program_options-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_python-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_random-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_regex-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_signals-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_system-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_test_exec_monitor-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_thread-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_timer-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_unit_test_framework-vc120-mt-1_55.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_wave-vc120-mt-1_55.lib"));



	    // Uncomment if you are using Slate UI
	    // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

	    // Uncomment if you are using online features
	    // PrivateDependencyModuleNames.Add("OnlineSubsystem");
	    // if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
	    // {
	    //		if (UEBuildConfiguration.bCompileSteamOSS == true)
	    //		{
	    //			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
	    //		}
	    // }
	}
}
