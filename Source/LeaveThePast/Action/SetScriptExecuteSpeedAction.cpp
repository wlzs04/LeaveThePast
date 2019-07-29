#include "SetScriptExecuteSpeedAction.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"
#include "XmlParser/Public/XmlFile.h"

USetScriptExecuteSpeedAction::USetScriptExecuteSpeedAction() :UActionBase()
{
	actionName = TEXT("SetScriptExecuteSpeed");
}

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
