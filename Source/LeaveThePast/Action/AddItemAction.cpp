#include "AddItemAction.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/LogManager.h"
#include "../Config/UserData.h"

void UAddItemAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("itemId"))
		{
			itemId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("itemNumber"))
		{
			itemNumber = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UAddItemAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			itemId = FCString::Atoi(*attributeValue);
		case 2:
			itemNumber = FCString::Atoi(*attributeValue);
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
	if (paramList.Num() > 1)
	{
		itemId = FCString::Atoi(*paramList[1]);
	}
	if(paramList.Num() > 2)
	{
		itemNumber = FCString::Atoi(*paramList[2]);
	}
}

void UAddItemAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UAddItemAction::ExecuteReal()
{
	UMainGameManager::GetInstance()->GetUserData()->AddItem(itemId, itemNumber);
	return FString();
}
