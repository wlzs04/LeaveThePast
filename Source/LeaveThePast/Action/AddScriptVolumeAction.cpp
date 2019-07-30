#include "AddScriptVolumeAction.h"
#include "../Manager/HelpManager.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Script/Chapter.h"
#include "../Script/Section.h"
#include "../Script/Paragraph.h"
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
			scriptItemData.chapter = attributeValue;
			isNext = false;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			scriptItemData.sectionId = FCString::Atoi(*attributeValue);
			isNext = false;
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			scriptItemData.paragraphId = FCString::Atoi(*attributeValue);
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
			scriptItemData.chapter = chapter->GetChapterIndexName();
			scriptItemData.sectionId = chapter->GetCurrentSection()->GetSectionId();
			scriptItemData.paragraphId = chapter->GetCurrentSection()->GetCurrentParagraph()->GetParagraphId()+1;
		}
	}

	scriptVolume->SetInfo(scriptItemData);
	return FString();
}