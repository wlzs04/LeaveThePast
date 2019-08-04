#include "SceneRecorder.h"
#include "../../Manager/LogManager.h"
#include "../../Manager/HelpManager.h"

void USceneRecorder::LoadRecorder(FXmlNode* xmlNode)
{
	for (FXmlAttribute attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("id"))
		{
			id = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("sceneName"))
		{
			sceneName = attributeValue;
		}
		else if (attributeName == TEXT("bgmId"))
		{
			bgmId = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s配置中存在未知属性:%s：%s！"), *GetClass()->GetName().Left(GetClass()->GetName().Len() - 8), *attributeName, *attributeValue));
		}
	}

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
				else
				{
					LogWarning(FString::Printf(TEXT("%s配置中存在未知属性:%s：%s！"), *GetClass()->GetName().Left(GetClass()->GetName().Len() - 8), *attributeName, *attributeValue));
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