#include "AddItemAction.h"
#include "../Manager/MainGameManager.h"

UAddItemAction::UAddItemAction() :UActionBase()
{
	actionName = TEXT("AddItem");
}

void UAddItemAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
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
	if (isCompleted == false && GetExecuteActor() != nullptr)
	{
		isCompleted = true;
	}
}

void UAddItemAction::ExecuteReal()
{
	isCompleted = false;
	UMainGameManager::GetInstance()->GetUserData()->AddItem(itemId, itemNumber);
}
