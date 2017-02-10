// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;

public class evaLUAtion2 : ModuleRules
{
    private string LibPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../Lib/")); }
    }

    public evaLUAtion2(TargetInfo Target)
    {
        bUseRTTI = true;

        string evaLUAtionDir = ModuleDirectory;

        bEnableExceptions = true;

        string LuaPath = Path.Combine(evaLUAtionDir, "../Lib/Lua-5.3.3");
        string LuaBridge = Path.Combine(evaLUAtionDir, "../Lib/LuaBridge");
        string BoostPath = Path.Combine(evaLUAtionDir, "../Lib/boost_1_62_0");

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] {
            evaLUAtionDir,
            Path.Combine(LuaPath, "include"),
            BoostPath,
            LuaBridge
        });

        string BoostLibPath = Path.Combine(BoostPath, "lib64-msvc-14.0");

        PublicAdditionalLibraries.Add(Path.Combine(LuaPath, "lua53.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_atomic-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_bzip2-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_chrono-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_context-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_coroutine-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_date_time-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_exception-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_filesystem-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_graph-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_iostreams-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_locale-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_log_setup-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_log-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_c99f-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_c99l-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_c99-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_tr1f-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_tr1l-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_math_tr1-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_prg_exec_monitor-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_program_options-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_python-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_random-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_regex-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_signals-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_system-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_test_exec_monitor-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_thread-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_timer-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_unit_test_framework-vc140-mt-1_62.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(BoostLibPath, "libboost_wave-vc140-mt-1_62.lib"));

        Definitions.Add(string.Format("WITH_LUA_BINDING=1"));

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