#include "StartScriptAction.h"
#include "../Manager/ScriptManager.h"

UStartScriptAction::UStartScriptAction() :UActionBase()
{
	actionName = TEXT("StartScript");
}

void UStartScriptAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
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
		isCompleted = true;
	}
}

void UStartScriptAction::ExecuteReal()
{
	isCompleted = false;
	UScriptManager::GetInstance()->StartMainScriptByNameIndex(chapterName,sectionId,paragraphId);
}
