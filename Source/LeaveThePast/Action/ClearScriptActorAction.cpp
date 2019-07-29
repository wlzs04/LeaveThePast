#include "ClearScriptActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Script/Chapter.h"

UClearScriptActorAction::UClearScriptActorAction() :UActionBase()
{
	actionName = TEXT("ClearScriptActor");
}

void UClearScriptActorAction::Load(FXmlNode* xmlNode)
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
			isCurrent = false;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			scriptRecorderIndfo.sectionId = FCString::Atoi(*attributeValue);
			isCurrent = false;
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			scriptRecorderIndfo.paragraphId = FCString::Atoi(*attributeValue);
			isCurrent = false;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UClearScriptActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UClearScriptActorAction::ExecuteReal()
{
	AActorBase* actor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);

	if (actor == nullptr)
	{
		LogError(FString::Printf(TEXT("指令：SetScriptActor，场景中不存在演员：%d"), actorInfoId));
		return FString();
	}
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
	actor->RemoveInteractedScript(scriptRecorderIndfo);

	return FString();
}