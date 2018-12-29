// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ToolbarButtonPluginStyle.h"

class FToolbarButtonPluginCommands : public TCommands<FToolbarButtonPluginCommands>
{
public:

	FToolbarButtonPluginCommands()
		: TCommands<FToolbarButtonPluginCommands>(TEXT("ToolbarButtonPlugin"), NSLOCTEXT("Contexts", "ToolbarButtonPlugin", "ToolbarButtonPlugin Plugin"), NAME_None, FToolbarButtonPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
