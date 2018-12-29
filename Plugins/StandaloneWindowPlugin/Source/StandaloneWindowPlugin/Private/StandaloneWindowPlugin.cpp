// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowPlugin.h"
#include "StandaloneWindowPluginStyle.h"
#include "StandaloneWindowPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "EditorStyle/Public/EditorStyleSet.h"
#include "SlateCore/Public/Styling/SlateBrush.h"
#include "Engine/Classes/Engine/ObjectLibrary.h"
#include "Widgets/Input/SButton.h"
#include "SlateCore/Public/Input/Reply.h"

#include "Classes/Kismet/GameplayStatics.h"

#include "Editor/UnrealEd/Public/FileHelpers.h"

//D:\EpicGames_Version14_9\UE_4.21\Engine\Source\Runtime\SlateCore\Public\Styling\SlateBrush.h
//D:\EpicGames_Version14_9\UE_4.21\Engine\Source\Editor\EditorStyle\Public\EditorStyleSet.h
static const FName StandaloneWindowPluginTabName("StandaloneWindowPlugin");

#define LOCTEXT_NAMESPACE "FStandaloneWindowPluginModule"

void FStandaloneWindowPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FStandaloneWindowPluginStyle::Initialize();
	FStandaloneWindowPluginStyle::ReloadTextures();

	FStandaloneWindowPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneWindowPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneWindowPluginModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FStandaloneWindowPluginModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FStandaloneWindowPluginModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWindowPluginTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneWindowPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneWindowPluginTabTitle", "StandaloneWindowPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FStandaloneWindowPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FStandaloneWindowPluginStyle::Shutdown();

	FStandaloneWindowPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneWindowPluginTabName);
}

FReply FStandaloneWindowPluginModule::LoadMap(const FString& mapName)
{	
	if (UWorld* pWorld = GEditor->GetEditorWorldContext().World())
	{
		FString longPackageName = "";
		FString longFileName = "";
		if (FPackageName::SearchForPackageOnDisk(mapName, &longPackageName, &longFileName))
		{
			FEditorFileUtils::SaveDirtyPackages(false, true, false, false);
			FEditorFileUtils::LoadMap(longPackageName, false, true);

			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}

TSharedRef<SDockTab> FStandaloneWindowPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TArray<FString> mapNames = TArray<FString>();

	if (UObjectLibrary* pObjectLibrary = UObjectLibrary::CreateLibrary(UWorld::StaticClass(), false, true))
	{
		pObjectLibrary->LoadAssetDataFromPath(TEXT("/Game/Levels"));
		TArray<FAssetData> assetData;
		pObjectLibrary->GetAssetDataList(assetData);
		//TODO: Try to find a way to only find *.umap files from this directory
		// and then dynamically populate the window to represent the total levels
		for (int32 i = 0; i < assetData.Num(); ++i)
		{
			FAssetData& data = assetData[i];
			FString name = data.AssetName.ToString();
			mapNames.Add(name);
		}
	}

	// Failsafe if we delete our maps
	if (mapNames.Num() < 2)
	{
		mapNames.Empty();
		mapNames.Add("ThirdPersonExampleMap");
		mapNames.Add("ThirdPersonExampleMap");
	}

	FText WidgetTextA = FText::Format(
		LOCTEXT("WindowWidgetText", "{0}"),
		FText::FromString(mapNames[0])
	);
	FText WidgetTextB = FText::Format(
		LOCTEXT("WindowWidgetText", "{0}"),
		FText::FromString(mapNames[1])
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			//.HAlign(HAlign_Fill)
			//.VAlign(VAlign_Fill)
			//.MinDesiredHeight(300.0f)
			//.MaxDesiredHeight(400.0f)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(0, 10, 20, 10) // Left, Top, Right, Bottom
					[
						SNew(STextBlock)
						.Text(WidgetTextA)
					]
					+ SHorizontalBox::Slot()
					.Padding(0, 10, 0, 10) // Left, Top, Right, Bottom
					[
						SNew(SButton)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.Text(LOCTEXT("Load", "Load"))
						.ToolTipText(LOCTEXT("Load_Tooltip", "Begins loading into Map A"))
						// MUST CAPTURE BY VALUE for the mapNames to be valid otherwise they go out of scope and die
						.OnClicked_Lambda([=]() 
						{
							return LoadMap(mapNames[0]);
						})
						//.OnClicked_Raw(this,&FStandaloneWindowPluginModule::LoadMapA)
					]
				]
				+SVerticalBox::Slot()
					.AutoHeight()
				//.HAlign(HAlign_Center)
				//.FillHeight(25.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(0, 10, 20, 10) // Left, Top, Right, Bottom
					[
						SNew(STextBlock)
						.Text(WidgetTextB)
					]
					+ SHorizontalBox::Slot()
					.Padding(0, 10, 0, 10) // Left, Top, Right, Bottom
					[
						SNew(SButton)
						.VAlign(VAlign_Center)
						.HAlign(HAlign_Center)
						.Text(LOCTEXT("Load", "Load"))
						.ToolTipText(LOCTEXT("Load_Tooltip", "Begins loading into Map B"))
						.OnClicked_Lambda([=]()
						{
							return LoadMap(mapNames[1]);
						})
						//.OnClicked_Raw(this, &FStandaloneWindowPluginModule::LoadMapB)
						//SNew(SImage)
						//.ColorAndOpacity(FLinearColor::Green)
					]
				]
			]
		];
}

void FStandaloneWindowPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(StandaloneWindowPluginTabName);
}

void FStandaloneWindowPluginModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FStandaloneWindowPluginCommands::Get().OpenPluginWindow);
}

void FStandaloneWindowPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FStandaloneWindowPluginCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneWindowPluginModule, StandaloneWindowPlugin)