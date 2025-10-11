// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class RppUnreal : ModuleRules
{
	public RppUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] 
			{
				// ... add public include paths required here ...
				Path.Combine(ModuleDirectory, "..", "ThirdParty", "Rpp"),
				Path.Combine(ModuleDirectory, "..", "ThirdParty", "Rpp", "rpp"),
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] 
			{
				// ... add other private include paths required here ...
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"Rpp",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}
