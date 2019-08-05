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
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			messageId = FCString::Atoi(*attributeValue);
			break;
		case 2:
			actionTime = FCString::Atof(*attributeValue);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
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