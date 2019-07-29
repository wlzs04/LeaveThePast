#include "AddScriptVolumeAction.h"
#include "../Manager/HelpManager.h"
#include "../Manager/ActorManager.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/LogManager.h"
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
		if (attributeName == TEXT("position"))
		{
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
		else if (attributeName == TEXT("chapter"))
		{
			scriptRecorderIndfo.chapter = attributeValue;
			isNext = false;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			scriptRecorderIndfo.sectionId = FCString::Atoi(*attributeValue);
			isNext = false;
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			scriptRecorderIndfo.paragraphId = FCString::Atoi(*attributeValue);
			isNext = false;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
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
	AScriptVolume* scriptVolume = (AScriptVolume*)UActorManager::GetInstance()->AddVolumeToSceneByVolumeInfo(TEXT("Script"), position);
	
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