// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CharMoveTest : ModuleRules
{
	public CharMoveTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "AIModule", "GameplayTasks", "NavigationSystem", "Niagara" });
	}
}
