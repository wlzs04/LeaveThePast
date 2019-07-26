#include "StartScriptAction.h"
#include "../Manager/ScriptManager.h"

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
	UScriptManager::GetInstance()->StartMainScriptByNameIndex(chapterName,sectionId,paragraphId);
	return FString();
}
