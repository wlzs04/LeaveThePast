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
	UActionBase::Load(xmlNode);
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
	if (isCompleted == false && GetExecuteActor() != nullptr)
	{
		isCompleted = true;
	}
}

void UPlayBGMAction::ExecuteReal()
{
	startTime = GWorld->GetTimeSeconds();
	currentTime = GWorld->GetTimeSeconds();
	isCompleted = false;

	ADirectorActor* directorActor = Cast<ADirectorActor>(GWorld->GetFirstPlayerController()->GetPawn());
	USoundCue* sound = UAudioManager::GetInstance()->GetAudioById(audioId);
	directorActor->StartPlayBGMSound(sound);
}