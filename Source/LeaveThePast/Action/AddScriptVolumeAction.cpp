#include "AddScriptVolumeAction.h"
#include "../Manager/HelpManager.h"

UAddScriptVolumeAction::UAddScriptVolumeAction() :UActionBase()
{
	actionName = TEXT("AddScriptVolume");
}

void UAddScriptVolumeAction::Load(FXmlNode* xmlNode)
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
		else if (attributeName == TEXT("position"))
		{
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
	}
}

void UAddScriptVolumeAction::Update()
{
	if (isCompleted == false)
	{
		isCompleted = true;
	}
}

void UAddScriptVolumeAction::ExecuteReal()
{
	isCompleted = false;


}

