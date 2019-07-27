#include "AddScriptVolumeAction.h"
#include "../Manager/HelpManager.h"
#include "../Manager/ActorManager.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/ScriptManager.h"
#include "../Script/Chapter.h"
#include "../Volume/ScriptVolume.h"
#include "../LeaveThePastGameModeBase.h"

UAddScriptVolumeAction::UAddScriptVolumeAction() :UActionBase()
{
	actionName = TEXT("AddScriptVolume");
}

void UAddScriptVolumeAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("isNext"))
		{
			isNext = FCString::ToBool(*attributeValue);
		}
		else if (attributeName == TEXT("position"))
		{
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
		else if (attributeName == TEXT("chapter"))
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

void UAddScriptVolumeAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UAddScriptVolumeAction::ExecuteReal()
{
	FActorSpawnParameters actorSpawnParameters;
	actorSpawnParameters.bAllowDuringConstructionScript = true;
	actorSpawnParameters.bNoFail = true;
	AScriptVolume* scriptVolume = UMainGameManager::GetInstance()->GetGameWorld()->SpawnActor<AScriptVolume>(AScriptVolume::StaticClass(),position, FRotator(0,0,0), actorSpawnParameters);
	
	if (isNext)
	{
		UChapter* chapter =  UScriptManager::GetInstance()->GetCurrentChapter();
		if (chapter != nullptr)
		{
			scriptRecorderIndfo.chapter = chapter->GetChapterIndexName();
			scriptRecorderIndfo.sectionId = chapter->GetCurrentSection()->GetSectionId();
			scriptRecorderIndfo.paragraphId = chapter->GetCurrentSection()->GetCurrentParagraph()->GetParagraphId()+1;
		}
	}

	scriptVolume->SetInfo(scriptRecorderIndfo);
	return FString();
}