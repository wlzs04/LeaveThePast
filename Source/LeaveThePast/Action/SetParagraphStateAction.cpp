#include "SetParagraphStateAction.h"
#include "../Manager/MainGameManager.h"
#include "../Script/Chapter.h"

USetParagraphStateAction::USetParagraphStateAction() :UActionBase()
{
	actionName = TEXT("SetParagraphState");
}

void USetParagraphStateAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("state"))
		{
			state = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("chapter"))
		{
			chapter = attributeValue;
			isCurrent = false;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			sectionId = FCString::Atoi(*attributeValue);
			isCurrent = false;
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			paragraphId = FCString::Atoi(*attributeValue);
			isCurrent = false;
		}
	}
}

void USetParagraphStateAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetParagraphStateAction::ExecuteReal()
{
	if (isCurrent)
	{
		UChapter* currentChapter = UScriptManager::GetInstance()->GetCurrentChapter();
		if (currentChapter != nullptr)
		{
			chapter = currentChapter->GetChapterIndexName();
			sectionId = currentChapter->GetCurrentSection()->GetSectionId();
			paragraphId = currentChapter->GetCurrentSection()->GetCurrentParagraph()->GetParagraphId();
		}
	}
	UUserData* userData = UMainGameManager::GetInstance()->GetUserData();
	userData->SetParagraphState(chapter, sectionId,paragraphId, state);
	return FString();
}