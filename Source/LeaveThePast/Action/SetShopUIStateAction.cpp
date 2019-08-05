#include "SetShopUIStateAction.h"
#include "../Manager/LogManager.h"
#include "../Manager/UIManager.h"

void USetShopUIStateAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("isShow"))
		{
			isShow = FCString::ToBool(*attributeValue);
		}
		else if (attributeName == TEXT("shopConfigName"))
		{
			shopConfigName = attributeValue;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetShopUIStateAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			isShow = FCString::ToBool(*attributeValue);
		case 2:
			shopConfigName = attributeValue;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void USetShopUIStateAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetShopUIStateAction::ExecuteReal()
{
	if (isShow)
	{
		UUIManager::GetInstance()->ShowShopUI(shopConfigName);
	}
	else
	{
		UUIManager::GetInstance()->HideShopUI();
	}

	return FString();
}

