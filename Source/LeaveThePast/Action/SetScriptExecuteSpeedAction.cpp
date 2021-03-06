#include "SetScriptExecuteSpeedAction.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"

void USetScriptExecuteSpeedAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("value"))
		{
			scriptExecuteSpeed = FCString::Atof(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetScriptExecuteSpeedAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			scriptExecuteSpeed = FCString::Atof(*attributeValue);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void USetScriptExecuteSpeedAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetScriptExecuteSpeedAction::ExecuteReal()
{
	UScriptManager::GetInstance()->SetScriptExecuteSpeed(scriptExecuteSpeed);
	return FString();
}
