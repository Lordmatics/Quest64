// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowPluginCommands.h"

#define LOCTEXT_NAMESPACE "FStandaloneWindowPluginModule"

void FStandaloneWindowPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "StandaloneWindowPlugin", "Bring up StandaloneWindowPlugin window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
