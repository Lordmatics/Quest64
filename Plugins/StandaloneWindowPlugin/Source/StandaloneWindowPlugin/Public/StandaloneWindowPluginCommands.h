// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "StandaloneWindowPluginStyle.h"

class FStandaloneWindowPluginCommands : public TCommands<FStandaloneWindowPluginCommands>
{
public:

	FStandaloneWindowPluginCommands()
		: TCommands<FStandaloneWindowPluginCommands>(TEXT("StandaloneWindowPlugin"), NSLOCTEXT("Contexts", "StandaloneWindowPlugin", "StandaloneWindowPlugin Plugin"), NAME_None, FStandaloneWindowPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};