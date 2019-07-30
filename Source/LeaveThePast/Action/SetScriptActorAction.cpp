#include "SetScriptActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"
#include "../Actor/ActorBase.h"
#include "../Script/Chapter.h"
#include "../Script/Section.h"
#include "../Script/Paragraph.h"

USetScriptActorAction::USetScriptActorAction() :UActionBase()
{
	actionName = TEXT("SetScriptActor");
}

void USetScriptActorAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
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

void USetScriptActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetScriptActorAction::ExecuteReal()
{
	AActorBase* actor =  UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);

	if (actor == nullptr)
	{
		LogError(FString::Printf(TEXT("指令：SetScriptActor，场景中不存在演员：%d"), actorInfoId));
		return FString();
	}
	if (isNext)
	{
		UChapter* chapter = UScriptManager::GetInstance()->GetCurrentChapter();
		if (chapter != nullptr)
		{
			scriptItemData.chapter = chapter->GetChapterIndexName();
			scriptItemData.sectionId = chapter->GetCurrentSection()->GetSectionId();
			scriptItemData.paragraphId = chapter->GetCurrentSection()->GetCurrentParagraph()->GetParagraphId() + 1;
		}
	}
	actor->AddInteractedScript(scriptItemData);

	return FString();
}

