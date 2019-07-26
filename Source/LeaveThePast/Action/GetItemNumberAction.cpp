#include "GetItemNumberAction.h"
#include "../Manager/MainGameManager.h"

UGetItemNumberAction::UGetItemNumberAction() :UActionBase()
{
	actionName = TEXT("GetItemNumber");
}

void UGetItemNumberAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("itemId"))
		{
			itemId = FCString::Atoi(*attributeValue);
		}
	}
}

void UGetItemNumberAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		itemId = FCString::Atoi(*paramList[1]);
	}
}

void UGetItemNumberAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UGetItemNumberAction::ExecuteReal()
{
	int itemNumber = UMainGameManager::GetInstance()->GetUserData()->GetItemNumberById(itemId);
	return FString::FromInt(itemNumber);
}

