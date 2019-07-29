#include "GetMoneyAction.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/LogManager.h"

UGetMoneyAction::UGetMoneyAction() :UActionBase()
{
	actionName = TEXT("GetMoney");
}

void UGetMoneyAction::Load(FXmlNode* xmlNode)
{
}

void UGetMoneyAction::Load(TArray<FString> paramList)
{
	
}

void UGetMoneyAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UGetMoneyAction::ExecuteReal()
{
	int moneyNumber = UMainGameManager::GetInstance()->GetUserData()->GetMoney();
	return FString::FromInt(moneyNumber);
}