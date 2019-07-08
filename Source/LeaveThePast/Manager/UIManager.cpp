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
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), widgetClass);

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

	URecorderBase* messageTipRecorder = UConfigManager::GetInstance()->GetConfigByNameId(UMessageTipRecorder::StaticClass(), id);
	if (messageTipRecorder != nullptr)
	{
		value = ((UMessageTipRecorder*)messageTipRecorder)->GetValue();
	}

	AddMessageTip(value);
}

void UUIManager::ShowTalkUI(FString talkValue, FString actorName, float continueTime, FString headImagePath, bool isLeft)
{
	talkUIWidget->AddToViewport();
	FOutputDeviceNull outputDeviceNull;
	bool executeSuccess = talkUIWidget->CallFunctionByNameWithArguments(*FString::Printf(TEXT("SetInfo %s %s %s %f %d"), *headImagePath, *actorName, *talkValue, continueTime, isLeft), outputDeviceNull, nullptr, true);
	if (!executeSuccess)
	{
		LogError("ShowTalkUI执行SetInfo蓝图函数失败！");
	}
}

void UUIManager::ShowMainUI()
{
	mainUIWidget->AddToViewport();
	FOutputDeviceNull outputDeviceNull;
	bool executeSuccess = mainUIWidget->CallFunctionByNameWithArguments(*FString::Printf(TEXT("SetInfo")), outputDeviceNull, nullptr, true);
	if (!executeSuccess)
	{
		LogError("ShowMainUI执行SetInfo蓝图函数失败！");
	}
}

void UUIManager::InitUI()
{
	mainUIWidget = LoadUIByName(TEXT("MainUI"));
	talkUIWidget = LoadUIByName(TEXT("TalkUI"));
}