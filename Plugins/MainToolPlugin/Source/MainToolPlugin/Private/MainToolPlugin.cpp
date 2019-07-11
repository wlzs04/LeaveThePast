#include "MainToolPlugin.h"
#include "MainToolPluginStyle.h"
#include "MainToolPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "Editor.h"
#include "Engine/Selection.h"
#include <LeaveThePast/Actor/ActorBase.h>
#include <LeaveThePast/Manager/ActorManager.h>
#include <LeaveThePast/Manager/LogManager.h>

static const FName MainToolPluginTabName("MainToolPlugin");

#define LOCTEXT_NAMESPACE "FMainToolPluginModule"

void FMainToolPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMainToolPluginStyle::Initialize();
	FMainToolPluginStyle::ReloadTextures();

	FMainToolPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMainToolPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMainToolPluginModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMainToolPluginModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMainToolPluginModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MainToolPluginTabName, FOnSpawnTab::CreateRaw(this, &FMainToolPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMainToolPluginTabTitle", "MainToolPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMainToolPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMainToolPluginStyle::Shutdown();

	FMainToolPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MainToolPluginTabName);
}

TSharedRef<SDockTab> FMainToolPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FMainToolPluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("MainToolPlugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				/*SNew(STextBlock)
				.Text(WidgetText)*/
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Right)
				[
					SNew(SButton)
					.Text(LOCTEXT("FMainToolPluginModule", "根据actorId刷新演员信息"))
					.OnClicked_Static(&FMainToolPluginModule::SetActorInfoToActorBPButtonClick)
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Right)
				[
					SNew(SButton)
					.Text(LOCTEXT("FMainToolPluginModule", "将当前场景的演员信息保存到表中"))
					.OnClicked_Static(&FMainToolPluginModule::SaveSceneActorToConfigButtonClick2)
					//.OnClicked(this, &FMainToolPluginModule::TestButtonClick2)
				]
			]
		];
}

FReply FMainToolPluginModule::SetActorInfoToActorBPButtonClick()
{
	ULogManager* logManager = NewObject<ULogManager>();
	logManager->Init();

	UActorManager* actorManager = NewObject<UActorManager>();
	actorManager->Init();

	TArray<UObject*> actorList;
	GEditor->GetSelectedActors()->GetSelectedObjects(AActorBase::StaticClass(), actorList);
	for (UObject* obj : actorList)
	{
		AActorBase* actor = (AActorBase*)obj;
		UActorInfoBase* actorInfo = actorManager->GetActorInfoById(actor->actorIdForEditor);
		if (actorInfo != nullptr)
		{
			actor->SetActorInfo(actorInfo);
			actor->Restart();
			UE_LOG(LogTemp, Log, TEXT("演员id：%d信息设置完成！"), actor->actorIdForEditor);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("演员id：%d信息不存在！"), actor->actorIdForEditor);
		}
	}
	return FReply::Handled();
}

FReply FMainToolPluginModule::SaveSceneActorToConfigButtonClick2()
{
	UE_LOG(LogTemp, Error, TEXT("此方法未完成！"));
	return FReply::Handled();
}

void FMainToolPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(MainToolPluginTabName);
}

void FMainToolPluginModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMainToolPluginCommands::Get().OpenPluginWindow);
}

void FMainToolPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMainToolPluginCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMainToolPluginModule, MainToolPlugin)