#include "MessageTipByIdAction.h"
#include "../Manager/LogManager.h"
#include "../Manager/UIManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/ConfigManager.h"
#include "../Config/Recorder/MessageTipRecorder.h"

void UMessageTipByIdAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			messageId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("actionTime"))
		{
			actionTime = FCString::Atof(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UMessageTipByIdAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		messageId = FCString::Atoi(*paramList[1]);
	}
	if (paramList.Num() > 2)
	{
		actionTime = FCString::Atof(*paramList[2]);
	}
}

void UMessageTipByIdAction::Update()
{
	if (isCompleted == false)
	{
		currentTime += UScriptManager::GetInstance()->GetScriptTickTime();
		if (currentTime < actionTime)
		{

		}
		else
		{
			Finish();
		}
	}
}

FString UMessageTipByIdAction::ExecuteReal()
{
	currentTime = 0;
	UMessageTipRecorder* messageTipRecorder = (UMessageTipRecorder*)UConfigManager::GetInstance()->GetConfigByNameId(UMessageTipRecorder::StaticClass(), TEXT("MessageTip"), messageId);
	if (messageTipRecorder != nullptr)
	{
		UUIManager::GetInstance()->AddMessageTip(messageTipRecorder->GetValue());
	}
	else
	{
		LogError(FString::Printf(TEXT("%s指令在MessageTip表中不存在Id:%d"), *actionName,messageId));
	}
	return FString();
}