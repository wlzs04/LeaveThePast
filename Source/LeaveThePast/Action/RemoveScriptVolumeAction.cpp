#include "RemoveScriptVolumeAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/MainGameManager.h"
#include "../Script/Chapter.h"
#include "../Script/Section.h"
#include "../Script/Paragraph.h"
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
		if (attributeName == TEXT("chapter"))
		{
			scriptRecorderInfo.chapter = attributeValue;
			isCurrent = false;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			scriptRecorderInfo.sectionId = FCString::Atoi(*attributeValue);
			isCurrent = false;
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			scriptRecorderInfo.paragraphId = FCString::Atoi(*attributeValue);
			isCurrent = false;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
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
			scriptRecorderInfo.chapter = chapter->GetChapterIndexName();
			scriptRecorderInfo.sectionId = chapter->GetCurrentSection()->GetSectionId();
			scriptRecorderInfo.paragraphId = chapter->GetCurrentSection()->GetCurrentParagraph()->GetParagraphId();
		}
	}
	FString volumeValue; 
	volumeValue.Append(scriptRecorderInfo.chapter + TEXT(" "));
	volumeValue.Append(FString::FromInt(scriptRecorderInfo.sectionId) + TEXT(" "));
	volumeValue.Append(FString::FromInt(scriptRecorderInfo.paragraphId));
	UActorManager::GetInstance()->RemoveVolumeByVolumeValue(volumeValue);

	return FString();
}
