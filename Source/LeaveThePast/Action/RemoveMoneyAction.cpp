#include "RemoveMoneyAction.h"
#include "../Manager/MainGameManager.h"

URemoveMoneyAction::URemoveMoneyAction() :UActionBase()
{
	actionName = TEXT("RemoveMoney");
}

void URemoveMoneyAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("number"))
		{
			number = FCString::Atoi(*attributeValue);
		}
	}
}

void URemoveMoneyAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		number = FCString::Atoi(*paramList[1]);
	}
}

void URemoveMoneyAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveMoneyAction::ExecuteReal()
{
	isCompleted = false;
	UMainGameManager::GetInstance()->GetUserData()->ReduceMoney(number);
	return FString();
}