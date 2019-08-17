#include "EndBattleAction.h"
#include "../Manager/BattleManager.h"
#include "../Manager/LogManager.h"

void UEndBattleAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
	}
}

void UEndBattleAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
	}
}

void UEndBattleAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UEndBattleAction::ExecuteReal()
{
	UBattleManager::GetInstance()->EndBattle();
	return FString();
}