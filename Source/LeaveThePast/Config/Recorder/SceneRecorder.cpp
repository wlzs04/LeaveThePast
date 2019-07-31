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
			int actorId = 0;
			for (FXmlAttribute attribute : childNode->GetAttributes())
			{
				FString attributeName = attribute.GetTag();
				FString attributeValue = attribute.GetValue();
				if (attributeName == TEXT("actorId"))
				{
					actorId = FCString::Atoi(*attributeValue);
				}
			}
			sceneActorIdList.Add(actorId);
		}
	}
}

FString USceneRecorder::GetSceneName()
{
	return sceneName;
}

int USceneRecorder::GetBGMId()
{
	return bgmId;
}

TArray<int> USceneRecorder::GetSceneActorIdList()
{
	return sceneActorIdList;
}