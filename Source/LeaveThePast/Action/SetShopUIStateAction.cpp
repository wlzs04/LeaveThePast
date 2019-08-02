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

