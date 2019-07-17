#include "SceneRecorder.h"
#include "../../Manager/LogManager.h"
#include "../../Manager/HelpManager.h"

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

			for (FXmlAttribute attribute:childNode->GetAttributes())
			{
				FString attributeName = attribute.GetTag();
				FString attributeValue = attribute.GetValue();

				if (attributeName == TEXT("actorId"))
				{
					sceneActorInfo.SetActorId(FCString::Atoi(*attributeValue));
				}
				else if(attributeName == TEXT("actorName"))
				{
					sceneActorInfo.SetActorName(attributeValue);
				}
				else if (attributeName == TEXT("defaultPosition"))
				{
					sceneActorInfo.SetDefaultPosition(UHelpManager::ConvertFStringToFVector(attributeValue));
				}
				else if (attributeName == TEXT("defaultRotation"))
				{
					sceneActorInfo.SetDefaultRotation(UHelpManager::ConvertFStringToFRotator(attributeValue));
				}
				else
				{
					LogWarning(FString::Printf(TEXT("场景Id:%d配置中存在未知属性:%s！"), id, *attributeName));
				}
			}
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
