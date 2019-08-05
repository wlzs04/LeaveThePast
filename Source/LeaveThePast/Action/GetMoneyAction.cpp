#include "GetMoneyAction.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/LogManager.h"
#include "../Config/UserData.h"

void UGetMoneyAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
	}
}

void UGetMoneyAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
	}
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