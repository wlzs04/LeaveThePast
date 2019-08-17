#include "EnterBattleAction.h"
#include "../Manager/BattleManager.h"
#include "../Manager/LogManager.h"

void UEnterBattleAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
	}
}

void UEnterBattleAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
	}
}

void UEnterBattleAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UEnterBattleAction::ExecuteReal()
{
	UBattleManager::GetInstance()->EnterBattle();
	return FString();
}