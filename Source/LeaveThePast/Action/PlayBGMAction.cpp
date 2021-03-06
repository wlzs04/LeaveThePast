#include "PlayBGMAction.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/AudioManager.h"
#include "Sound/SoundCue.h"
#include "../Manager/LogManager.h"

void UPlayBGMAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("audioId"))
		{
			audioId = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UPlayBGMAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			audioId = FCString::Atoi(*attributeValue);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void UPlayBGMAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UPlayBGMAction::ExecuteReal()
{
	ADirectorActor* directorActor = ADirectorActor::GetInstance();
	USoundCue* sound = UAudioManager::GetInstance()->GetAudioById(audioId);
	if (sound != nullptr)
	{
		directorActor->StartPlayBGMSound(sound);
	}
	else
	{
		LogError(FString::Printf(TEXT("指令:%s配置中audioId:%d不存在！"), *actionName, audioId));
	}
	return FString();
}