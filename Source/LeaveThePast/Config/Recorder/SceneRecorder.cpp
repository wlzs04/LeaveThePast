#include "SceneRecorder.h"
#include "../../Manager/LogManager.h"
#include "../../Manager/HelpManager.h"

void FSceneActorInfo::LoadFromXmlNode(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();

		if (attributeName == TEXT("actorId"))
		{
			actorId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("actorName"))
		{
			SetActorName(attributeValue);
		}
		else if (attributeName == TEXT("position"))
		{
			SetPosition(UHelpManager::ConvertFStringToFVector(attributeValue));
		}
		else if (attributeName == TEXT("rotation"))
		{
			SetRotation(UHelpManager::ConvertFStringToFRotator(attributeValue));
		}
	}
}

void USceneRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	URecorderBase::LoadRecorder(xmlNode);

	sceneName = xmlNode->GetAttribute(TEXT("sceneName"));
	bgmId = FCString::Atoi(*xmlNode->GetAttribute(TEXT("bgmId")));

	for (FXmlNode* childNode : xmlNode->GetChildrenNodes())
	{
		if (childNode->GetTag() == TEXT("SceneActorInfo"))
		{
			FSceneActorInfo sceneActorInfo;
			sceneActorInfo.LoadFromXmlNode(childNode);
			sceneActorList.Add(sceneActorInfo);
		}
	}
}

FString USceneRecorder::GetRecordName()
{
	return TEXT("Scene");
}

FString USceneRecorder::GetSceneName()
{
	return sceneName;
}

int USceneRecorder::GetBGMId()
{
	return bgmId;
}

TArray<FSceneActorInfo> USceneRecorder::GetSceneActorList()
{
	return sceneActorList;
}
