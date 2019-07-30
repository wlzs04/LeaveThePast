#include "MessageTipAction.h"
#include "../Manager/LogManager.h"
#include "../Manager/UIManager.h"

UMessageTipAction::UMessageTipAction() :UActionBase()
{
	actionName = TEXT("MessageTip");
}

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

void UMessageTipAction::Update()
{
	if (isCompleted == false)
	{
		currentTime = GWorld->GetTimeSeconds();
		if (currentTime - startTime < actionTime)
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
	startTime = GWorld->GetTimeSeconds();
	currentTime = GWorld->GetTimeSeconds();
	UUIManager::GetInstance()->AddMessageTip(text);
	return FString();
}

