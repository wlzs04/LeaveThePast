// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MainToolPluginStyle.h"

class FMainToolPluginCommands : public TCommands<FMainToolPluginCommands>
{
public:

	FMainToolPluginCommands()
		: TCommands<FMainToolPluginCommands>(TEXT("MainToolPlugin"), NSLOCTEXT("Contexts", "MainToolPlugin", "MainToolPlugin Plugin"), NAME_None, FMainToolPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};