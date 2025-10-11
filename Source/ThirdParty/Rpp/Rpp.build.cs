// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class Rpp : ModuleRules
{
	public Rpp(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PublicSystemIncludePaths.Add(ModuleDirectory);
		PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "rpp"));
		PublicIncludePaths.Add(ModuleDirectory);
	}
}
