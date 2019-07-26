#include "SetScriptExecuteSpeedAction.h"
#include "..\Manager\ScriptManager.h"

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
