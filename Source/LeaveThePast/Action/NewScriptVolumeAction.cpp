#include "NewScriptVolumeAction.h"
#include "../Manager/HelpManager.h"

UNewScriptVolumeAction::UNewScriptVolumeAction() :UActionBase()
{
	actionName = TEXT("NewScriptVolume");
}

void UNewScriptVolumeAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("isNext"))
		{
			isNext = FCString::ToBool(*attributeValue);
		}
		else if(attributeName == TEXT("position"))
		{
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
	}
}

void UNewScriptVolumeAction::Update()
{
	if (isCompleted == false)
	{
		isCompleted = true;
	}
}

void UNewScriptVolumeAction::ExecuteReal()
{
	isCompleted = false;
	
}
