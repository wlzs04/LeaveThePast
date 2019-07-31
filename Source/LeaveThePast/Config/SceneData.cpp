#include "SceneData.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Manager/HelpManager.h"
#include "../Manager/LogManager.h"

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
		else
		{
			LogWarning(FString::Printf(TEXT("SceneActorData配置中存在未知属性:%s:%s！"), *attributeName,*attributeValue));
		}
	}

	for (FXmlNode* childNode : xmlNode->GetChildrenNodes())
	{
		FString nodeName = childNode->GetTag();
		if (nodeName == TEXT("ScriptItemData"))
		{
			FScriptItemData scriptItemData;
			scriptItemData.LoadFromXmlNode(childNode);
			scriptItemDataList.Add(scriptItemData);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("SceneActor中存在未知节点:%s！"), *nodeName));
		}
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
		else
		{
			LogWarning(FString::Printf(TEXT("SceneVolume配置中存在未知属性:%s:%s！"), *attributeName, *attributeValue));
		}
	}
}