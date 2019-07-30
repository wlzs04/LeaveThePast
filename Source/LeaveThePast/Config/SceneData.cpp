#include "SceneData.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/HelpManager.h"

void USceneActorData::LoadFromXmlNode(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();

		if (attributeName == TEXT("id"))
		{
			actorId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("position"))
		{
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
		else if (attributeName == TEXT("rotation"))
		{
			rotation = UHelpManager::ConvertFStringToFRotator(attributeValue);
		}
	}

	for (FXmlNode* childNode : xmlNode->GetChildrenNodes())
	{
		FScriptItemData scriptItemData;
		scriptItemData.LoadFromXmlNode(childNode);
		scriptItemDataList.Add(scriptItemData);
	}
}

void USceneVolumeData::LoadFromXmlNode(FXmlNode* xmlNode)
{
	volumeType = xmlNode->GetTag();
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();

		if (attributeName == TEXT("position"))
		{
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
		else if (attributeName == TEXT("value"))
		{
			value = attributeValue;
		}
	}
}