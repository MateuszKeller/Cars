// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MadBumbums : ModuleRules
{
	public MadBumbums(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ChaosVehicles", "PhysicsCore" });
	}
}
