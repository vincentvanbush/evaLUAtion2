// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "VictoryFileFunctions.generated.h"

template <class FunctorType>
class PlatformFileFunctor : public IPlatformFile::FDirectoryVisitor	//GenericPlatformFile.h
{
public:

	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
	{
		return Functor(FilenameOrDirectory, bIsDirectory);
	}

	PlatformFileFunctor(FunctorType&& FunctorInstance)
		: Functor(MoveTemp(FunctorInstance))
	{
	}

private:
	FunctorType Functor;
};

template <class Functor>
PlatformFileFunctor<Functor> MakeDirectoryVisitor(Functor&& FunctorInstance)
{
	return PlatformFileFunctor<Functor>(MoveTemp(FunctorInstance));
}

/**
 * 
 */
UCLASS()
class EVALUATION2_API UVictoryFileFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = VictoryFileFunctions)
	static bool LoadTextFile(FString Path, TArray<FString> &Lines)
	{
		FString FileStr;
		bool ret = FFileHelper::LoadFileToString(FileStr, *Path);
		if (ret)
			FileStr.ParseIntoArrayLines(Lines);
		return ret;
	}

	UFUNCTION(BlueprintCallable, Category = VictoryFileFunctions)
	static bool SaveTextFile(FString Path, FString Text)
	{
		return FFileHelper::SaveStringToFile(Text, *Path);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Victory Get All Files
	//      Optional File Extension Filter!!!  by Rama
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	UFUNCTION(BlueprintCallable, Category = VictoryFileFunctions)
	static bool GetFiles(const FString& FullPathOfBaseDir, TArray<FString>& FilenamesOut, bool Recursive = false, const FString& FilterByExtension = "", bool IncludeDirectories = true, bool DirectoriesOnly = false)
	{
		//Format File Extension, remove the "." if present
		const FString FileExt = FilterByExtension.Replace(TEXT("."), TEXT("")).ToLower();

		FString Str;
		auto FilenamesVisitor = MakeDirectoryVisitor(
			[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			//Files
			if ((!bIsDirectory && !DirectoriesOnly) || (bIsDirectory && IncludeDirectories))
			{
				//Filter by Extension
				if (FileExt != "")
				{
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					//Filter by Extension
					if (FPaths::GetExtension(Str).ToLower() == FileExt)
					{
						if (Recursive)
						{
							FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
						}
						else
						{
							FilenamesOut.Push(Str);
						}
					}
				}

				//Include All Filenames!
				else
				{
					//Just the Directory
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					if (Recursive)
					{
						FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
					}
					else
					{
						FilenamesOut.Push(Str);
					}
				}
			}
			return true;
		}
		);
		if (Recursive)
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
		}
		else
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
		}
	}
	
	
};
