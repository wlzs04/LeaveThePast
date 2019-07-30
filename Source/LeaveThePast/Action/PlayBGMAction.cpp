#include "PlayBGMAction.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/AudioManager.h"
#include "Sound/SoundCue.h"
#include "../Manager/LogManager.h"

UPlayBGMAction::UPlayBGMAction() :UActionBase()
{
	actionName = TEXT("PlayBGM");
}

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
	directorActor->StartPlayBGMSound(sound);
	return FString();
}