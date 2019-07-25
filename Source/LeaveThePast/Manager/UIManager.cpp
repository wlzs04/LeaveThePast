#include "UIManager.h"
#include "ConfigManager.h"
#include "LogManager.h"
#include "MainGameManager.h"
#include "../Action/OptionAction.h"
#include "../Actor/DirectorActor.h"
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

UUserWidget* UUIManager::LoadUIByName(FString uiName, FString foldName)
{
	FString uiPath = TEXT("WidgetBlueprint'/Game/GameContent/UI/")+ foldName + uiName + TEXT(".") + uiName + TEXT("_C'");
	UClass* widgetClass = LoadClass<UUserWidget>(NULL, *uiPath);
	UUserWidget* widget = CreateWidget<UUserWidget>(GWorld->GetFirstPlayerController(), widgetClass);

	return widget;
}

void UUIManager::ShowInitUI()
{
	LoadUIByName(TEXT("InitUI"))->AddToViewport();
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
	if (!talkUIWidget->IsInViewport())
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
	if (!mainUIWidget->IsInViewport())
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

bool UUIManager::IsShowMainUI()
{
	return mainUIWidget->IsInViewport();
}

void UUIManager::ShowMenuUI()
{
	if (!menuUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->AddCanOnlyControlUINumber();
		menuUIWidget->AddToViewport();
	}
}

void UUIManager::HideMenuUI()
{
	if (menuUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->RemoveCanOnlyControlUINumber();
		menuUIWidget->RemoveFromParent();
	}
}

bool UUIManager::IsShowMenuUI()
{
	return menuUIWidget->IsInViewport();
}

void UUIManager::ShowShopUI(FString shopConfigName)
{
	if (!shopUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->AddCanOnlyControlUINumber();
		shopUIWidget->AddToViewport();
	}

	UFunction* functionSetInfo = shopUIWidget->FindFunction(TEXT("SetInfo"));
	if (functionSetInfo)
	{
		shopUIWidget->ProcessEvent(functionSetInfo, &shopConfigName);
	}
}

void UUIManager::HideShopUI()
{
	if (shopUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->RemoveCanOnlyControlUINumber();
		shopUIWidget->RemoveFromParent();
	}
}

bool UUIManager::IsShowShopUI()
{
	return shopUIWidget->IsInViewport();
}

void UUIManager::ShowDebugUI()
{
	if (!debugUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->AddCanOnlyControlUINumber();
		debugUIWidget->AddToViewport();
	}
}

void UUIManager::HideDebugUI()
{
	if (debugUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->RemoveCanOnlyControlUINumber();
		debugUIWidget->RemoveFromParent();
	}
}

bool UUIManager::IsShowDebugUI()
{
	return debugUIWidget->IsInViewport();
}

void UUIManager::ShowMapUI()
{
	if (!mapUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->AddCanOnlyControlUINumber();
		mapUIWidget->AddToViewport();
	}
}

void UUIManager::HideMapUI()
{
	if (mapUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->RemoveCanOnlyControlUINumber();
		mapUIWidget->RemoveFromParent();
	}
}

bool UUIManager::IsShowMapUI()
{
	return mapUIWidget->IsInViewport();
}

void UUIManager::ShowPauseUI()
{
	if (!pauseUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->AddCanOnlyControlUINumber();
		pauseUIWidget->AddToViewport();
		UMainGameManager::GetInstance()->StopTime();
	}
}

void UUIManager::HidePauseUI()
{
	if (pauseUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->RemoveCanOnlyControlUINumber();
		pauseUIWidget->RemoveFromParent();
		UMainGameManager::GetInstance()->StartTime();
	}
}

bool UUIManager::IsShowPauseUI()
{
	return pauseUIWidget->IsInViewport();
}

void UUIManager::ShowOptionUI(UOptionAction* optionAction)
{
	if (!optionUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->AddCanOnlyControlUINumber();
		optionUIWidget->AddToViewport();
	}
	UFunction* functionSetInfo = optionUIWidget->FindFunction(TEXT("SetInfo"));
	if (functionSetInfo)
	{
		optionUIWidget->ProcessEvent(functionSetInfo , &optionAction);
	}
}

void UUIManager::HideOptionUI()
{
	if (optionUIWidget->IsInViewport())
	{
		ADirectorActor::GetInstance()->RemoveCanOnlyControlUINumber();
		optionUIWidget->RemoveFromParent();
	}
}

bool UUIManager::IsShowOptionUI()
{
	return optionUIWidget->IsInViewport();
}

void UUIManager::InitUI()
{
	mainUIWidget = LoadUIByName(TEXT("MainUI"));
	talkUIWidget = LoadUIByName(TEXT("TalkUI"));
	menuUIWidget = LoadUIByName(TEXT("MenuUI"));
	shopUIWidget = LoadUIByName(TEXT("ShopUI"),TEXT("Shop/"));
	debugUIWidget = LoadUIByName(TEXT("DebugUI"));
	mapUIWidget = LoadUIByName(TEXT("MapUI")); 
	pauseUIWidget = LoadUIByName(TEXT("PauseUI"));
	optionUIWidget = LoadUIByName(TEXT("OptionUI"));
}