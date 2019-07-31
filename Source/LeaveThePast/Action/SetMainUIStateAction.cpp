#include "SetMainUIStateAction.h"
#include "../Manager/LogManager.h"
#include "../Manager/UIManager.h"

void USetMainUIStateAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("isShow"))
		{
			isShow = FCString::ToBool(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetMainUIStateAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetMainUIStateAction::ExecuteReal()
{
	if (isShow)
	{
		UUIManager::GetInstance()->ShowMainUI();
	}
	else
	{
		UUIManager::GetInstance()->HideMainUI();
	}
	
	return FString();
}