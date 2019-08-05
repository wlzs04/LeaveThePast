#include "RemoveItemAction.h"
#include "../Manager/MainGameManager.h"
#include "../Config/UserData.h"
#include "../Manager/LogManager.h"

void URemoveItemAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("itemId"))
		{
			itemId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("number"))
		{
			number = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void URemoveItemAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			itemId = FCString::Atoi(*paramList[1]);
			break;
		case 2:
			number = FCString::Atoi(*paramList[1]);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void URemoveItemAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveItemAction::ExecuteReal()
{
	UMainGameManager::GetInstance()->GetUserData()->ReduceItem(itemId,number);
	return FString();
}

