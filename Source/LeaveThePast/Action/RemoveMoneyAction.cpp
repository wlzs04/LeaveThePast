#include "RemoveMoneyAction.h"
#include "../Manager/MainGameManager.h"
#include "../Config/UserData.h"
#include "../Manager/LogManager.h"

URemoveMoneyAction::URemoveMoneyAction() :UActionBase()
{
	actionName = TEXT("RemoveMoney");
}

void URemoveMoneyAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("number"))
		{
			number = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
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
	UMainGameManager::GetInstance()->GetUserData()->ReduceMoney(number);
	return FString();
}