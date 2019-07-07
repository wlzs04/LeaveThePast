#include "UIManager.h"
#include "ConfigManager.h"
#include "LogManager.h"
#include "../Config/Recorder/MessageTipRecorder.h"

UUIManager* UUIManager::uiManager = nullptr;

UUIManager::UUIManager():UObject()
{

}

UUIManager* UUIManager::GetInstance()
{
	return uiManager;
}

void UUIManager::Init()
{
	UUIManager::uiManager = this;
																																  //UUserWidget* userWidget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);
}

void UUIManager::AddMessageTip(FString value)
{
	UClass* widgetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/GameContent/UI/MessageTipUI.MessageTipUI_C'"));//
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), widgetClass);
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

void UUIManager::SetTalkUI(FString talkValue, FString actorName, float continueTime, FString headImagePath, bool isLeft)
{
	UClass* widgetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/GameContent/UI/TalkUI.TalkUI_C'"));
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), widgetClass);
	widget->AddToViewport();
	FOutputDeviceNull outputDeviceNull;
	bool executeSuccess = widget->CallFunctionByNameWithArguments(*FString::Printf(TEXT("SetInfo %s %s %s %f %d"), *headImagePath, *actorName, *talkValue, continueTime, isLeft), outputDeviceNull, nullptr, true);
	if (!executeSuccess)
	{
		LogError("SetTalkUI执行SetInfo蓝图函数失败！");
	}
}

UUserWidget* UUIManager::ShowUIByName(FString uiName)
{
	FString uiPath = TEXT("WidgetBlueprint'/Game/GameContent/UI/")+ uiName + TEXT(".") + uiName +TEXT("_C'");
	UClass* widgetClass = LoadClass<UUserWidget>(NULL, *uiPath);
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), widgetClass);
	widget->AddToViewport();
	return widget;
}
