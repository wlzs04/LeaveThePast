#include "StopScriptAction.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"

void UStopScriptAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
	}
}

void UStopScriptAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UStopScriptAction::ExecuteReal()
{
	UScriptManager::GetInstance()->StopCurrentScript();
	return FString();
}

