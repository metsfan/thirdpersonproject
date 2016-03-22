
// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ThirdPersonProjectTarget : TargetRules
{
	public ThirdPersonProjectTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
        //bUsesSteam = true;
    }

    //
    // TargetRules interface.
    //

    public override void SetupBinaries(
        TargetInfo Target,
        ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
        ref List<string> OutExtraModuleNames
        )
    {
        OutExtraModuleNames.Add("ThirdPersonProject");
        OutExtraModuleNames.Add("Slate");
        OutExtraModuleNames.Add("SlateCore");
        OutExtraModuleNames.Add("UMG");
	}
}