// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ToolbarButtonPlugin.h"
#include "ToolbarButtonPluginStyle.h"
#include "ToolbarButtonPluginCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"

static const FName ToolbarButtonPluginTabName("ToolbarButtonPlugin");

#define LOCTEXT_NAMESPACE "FToolbarButtonPluginModule"

void FToolbarButtonPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	// Setup plugin
	FToolbarButtonPluginStyle::Initialize();
	FToolbarButtonPluginStyle::ReloadTextures();
	FToolbarButtonPluginCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FToolbarButtonPluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FToolbarButtonPluginModule::PluginButtonClicked),
		FCanExecuteAction());	

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		// Adds functionality to the bottom of Window->Layout->See Bottom
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FToolbarButtonPluginModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		// Adds functionality immediately after the Settings button on the main level toolbar above the game window
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FToolbarButtonPluginModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FToolbarButtonPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FToolbarButtonPluginStyle::Shutdown();

	FToolbarButtonPluginCommands::Unregister();
}

void FToolbarButtonPluginModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FToolbarButtonPluginModule::PluginButtonClicked()")),
							FText::FromString(TEXT("ToolbarButtonPlugin.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FToolbarButtonPluginModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FToolbarButtonPluginCommands::Get().PluginAction);
}

void FToolbarButtonPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FToolbarButtonPluginCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToolbarButtonPluginModule, ToolbarButtonPlugin)