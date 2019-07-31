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
