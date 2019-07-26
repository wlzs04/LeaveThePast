#include "PlayBGMAction.h"
#include "Engine/World.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/AudioManager.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Sound/SoundCue.h"

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