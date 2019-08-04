#include "MessageTipAction.h"
#include "../Manager/LogManager.h"
#include "../Manager/UIManager.h"
#include "../Manager/ScriptManager.h"

void UMessageTipAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute:xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("text"))
		{
			text = attributeValue;
		}
		else if(attributeName == TEXT("actionTime"))
		{
			actionTime = FCString::Atof(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UMessageTipAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		text = paramList[1];
	}
	if (paramList.Num() > 2)
	{
		actionTime = FCString::Atof(*paramList[2]);
	}
}

void UMessageTipAction::Update()
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

FString UMessageTipAction::ExecuteReal()
{
	currentTime = 0;
	UUIManager::GetInstance()->AddMessageTip(text);
	return FString();
}

