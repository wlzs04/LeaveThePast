#include "GetMoneyAction.h"
#include "../Manager/MainGameManager.h"

UGetMoneyAction::UGetMoneyAction() :UActionBase()
{
	actionName = TEXT("GetMoney");
}

void UGetMoneyAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
}

void UGetMoneyAction::Load(TArray<FString> paramList)
{
	
}

void UGetMoneyAction::Update()
{
	if (isCompleted == false)
	{
		isCompleted = true;
	}
}

FString UGetMoneyAction::ExecuteReal()
{
	isCompleted = false;
	int moneyNumber = UMainGameManager::GetInstance()->GetUserData()->GetMoney();
	return FString::FromInt(moneyNumber);
}