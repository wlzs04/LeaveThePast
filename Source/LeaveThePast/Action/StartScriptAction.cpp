#include "StartScriptAction.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"

UStartScriptAction::UStartScriptAction() :UActionBase()
{
	actionName = TEXT("StartScript");
}

void UStartScriptAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("chapterName"))
		{
			chapterName = attributeValue;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			sectionId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			paragraphId = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UStartScriptAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UStartScriptAction::ExecuteReal()
{
	UScriptManager::GetInstance()->StartScript(chapterName,sectionId,paragraphId);
	return FString();
}
