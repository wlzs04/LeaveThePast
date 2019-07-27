#include "RemoveScriptVolumeAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/MainGameManager.h"
#include "../Script/Chapter.h"
#include "../Volume/ScriptVolume.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "Engine/Public/EngineUtils.h"

URemoveScriptVolumeAction::URemoveScriptVolumeAction() :UActionBase()
{
	actionName = TEXT("RemoveScriptVolume");
}

void URemoveScriptVolumeAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("isCurrent"))
		{
			isCurrent = FCString::ToBool(*attributeValue);
		}
		if (attributeName == TEXT("chapter"))
		{
			scriptRecorderIndfo.chapter = attributeValue;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			scriptRecorderIndfo.sectionId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			scriptRecorderIndfo.paragraphId = FCString::Atoi(*attributeValue);
		}
	}
}

void URemoveScriptVolumeAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveScriptVolumeAction::ExecuteReal()
{
	if (isCurrent)
	{
		UChapter* chapter = UScriptManager::GetInstance()->GetCurrentChapter();
		if (chapter != nullptr)
		{
			scriptRecorderIndfo.chapter = chapter->GetChapterIndexName();
			scriptRecorderIndfo.sectionId = chapter->GetCurrentSection()->GetSectionId();
			scriptRecorderIndfo.paragraphId = chapter->GetCurrentSection()->GetCurrentParagraph()->GetParagraphId();
		}
	}
	TActorIterator<AScriptVolume> actorItr = TActorIterator<AScriptVolume>(UMainGameManager::GetInstance()->GetGameWorld(), AScriptVolume::StaticClass());
	for (actorItr; actorItr; ++actorItr)
	{
		AScriptVolume* volume = *actorItr;
		if (volume->GetScriptInfo()==scriptRecorderIndfo)
		{
			volume->Destroy();
		}
	}

	return FString();
}
