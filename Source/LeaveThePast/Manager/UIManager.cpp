#include "UIManager.h"
#include "ConfigManager.h"
#include "LogManager.h"
#include "../Config/Recorder/MessageTipRecorder.h"

UUIManager* UUIManager::uiManager = nullptr;

UUIManager* UUIManager::GetInstance()
{
	return uiManager;
}

void UUIManager::Init()
{
	UUIManager::uiManager = this;
	InitUI();
}

UUserWidget* UUIManager::LoadUIByName(FString uiName)
{
	FString uiPath = TEXT("WidgetBlueprint'/Game/GameContent/UI/") + uiName + TEXT(".") + uiName + TEXT("_C'");
	UClass* widgetClass = LoadClass<UUserWidget>(NULL, *uiPath);
	UUserWidget* widget = CreateWidget<UUserWidget>(GWorld->GetFirstPlayerController(), widgetClass);

	return widget;
}

void UUIManager::AddMessageTip(FString value)
{
	UUserWidget* widget = LoadUIByName(TEXT("MessageTipUI"));
	widget->AddToViewport();
	FOutputDeviceNull outputDeviceNull;
	bool executeSuccess = widget->CallFunctionByNameWithArguments(*FString::Printf(TEXT("SetInfo %s"), *value), outputDeviceNull, nullptr,true);
	if (!executeSuccess)
	{
		LogError("AddMessageTip执行SetInfo蓝图函数失败！");
	}
}

void UUIManager::AddMessageTipById(int id)
{
	FString value = TEXT("");

	URecorderBase* messageTipRecorder = UConfigManager::GetInstance()->GetConfigByNameId(UMessageTipRecorder::StaticClass(),TEXT("MessageTip"), id);
	if (messageTipRecorder != nullptr)
	{
		value = ((UMessageTipRecorder*)messageTipRecorder)->GetValue();
	}

	AddMessageTip(value);
}

void UUIManager::ShowTalkUI(FString talkValue, FString actorName, float continueTime, FString headImagePath, bool isLeft)
{
	if (talkUIWidget->GetParent() == nullptr)
	{
		talkUIWidget->AddToViewport();
	}
	
	FOutputDeviceNull outputDeviceNull;
	bool executeSuccess = talkUIWidget->CallFunctionByNameWithArguments(*FString::Printf(TEXT("SetInfo %s %s %s %f %d"), *headImagePath, *actorName, *talkValue, continueTime, isLeft), outputDeviceNull, nullptr, true);
	if (!executeSuccess)
	{
		LogError("ShowTalkUI执行SetInfo蓝图函数失败！");
	}
}

void UUIManager::ShowMainUI()
{
	if (mainUIWidget->GetParent() == nullptr)
	{
		mainUIWidget->AddToViewport();
	}

	FOutputDeviceNull outputDeviceNull;
	bool executeSuccess = mainUIWidget->CallFunctionByNameWithArguments(*FString::Printf(TEXT("SetInfo")), outputDeviceNull, nullptr, true);
	if (!executeSuccess)
	{
		LogError("ShowMainUI执行SetInfo蓝图函数失败！");
	}
}

void UUIManager::HideMainUI()
{
	mainUIWidget->RemoveFromParent();
}

void UUIManager::ShowMenuUI()
{
	menuUIWidget->AddToViewport();
}

void UUIManager::HideMenuUI()
{
	menuUIWidget->RemoveFromParent();
}

void UUIManager::ShowShopUI(FString shopConfigName)
{
	shopUIWidget->AddToViewport();

	UFunction* functionSetInfo = shopUIWidget->FindFunction(TEXT("SetInfo"));
	if (functionSetInfo)
	{
		shopUIWidget->ProcessEvent(functionSetInfo, &shopConfigName);
	}
}

void UUIManager::HideShopUI()
{
	shopUIWidget->AddToViewport();
}

void UUIManager::ShowDebugUI()
{
	debugUIWidget->AddToViewport();
}

void UUIManager::HideDebugUI()
{
	debugUIWidget->RemoveFromParent();
}

void UUIManager::ShowMapUI()
{
	mapUIWidget->AddToViewport();
}

void UUIManager::HideMapUI()
{
	mapUIWidget->RemoveFromParent();
}

void UUIManager::ShowPauseUI()
{
	pauseUIWidget->AddToViewport();
}

void UUIManager::HidePauseUI()
{
	pauseUIWidget->RemoveFromParent();
}

void UUIManager::InitUI()
{
	mainUIWidget = LoadUIByName(TEXT("MainUI"));
	talkUIWidget = LoadUIByName(TEXT("TalkUI"));
	menuUIWidget = LoadUIByName(TEXT("MenuUI"));
	shopUIWidget = LoadUIByName(TEXT("ShopUI"));
	debugUIWidget = LoadUIByName(TEXT("DebugUI"));
	mapUIWidget = LoadUIByName(TEXT("MapUI"));
	pauseUIWidget = LoadUIByName(TEXT("PauseUI"));
}