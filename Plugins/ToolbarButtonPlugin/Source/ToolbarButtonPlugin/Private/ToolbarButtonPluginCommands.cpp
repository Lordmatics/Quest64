// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ToolbarButtonPluginCommands.h"

#define LOCTEXT_NAMESPACE "FToolbarButtonPluginModule"

void FToolbarButtonPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ToolbarButtonPlugin", "Execute ToolbarButtonPlugin action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
