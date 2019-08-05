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

void USetMainUIStateAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			isShow = FCString::ToBool(*attributeValue);
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
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