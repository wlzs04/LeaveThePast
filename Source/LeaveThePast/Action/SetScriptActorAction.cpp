#include "SetScriptActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"
#include "../Script/Chapter.h"

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
			scriptRecorderIndfo.chapter = chapter->GetChapterIndexName();
			scriptRecorderIndfo.sectionId = chapter->GetCurrentSection()->GetSectionId();
			scriptRecorderIndfo.paragraphId = chapter->GetCurrentSection()->GetCurrentParagraph()->GetParagraphId() + 1;
		}
	}
	actor->AddInteractedScript(scriptRecorderIndfo);

	return FString();
}

