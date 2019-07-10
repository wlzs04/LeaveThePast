// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MainToolPluginCommands.h"

#define LOCTEXT_NAMESPACE "FMainToolPluginModule"

void FMainToolPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MainToolPlugin", "Bring up MainToolPlugin window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
