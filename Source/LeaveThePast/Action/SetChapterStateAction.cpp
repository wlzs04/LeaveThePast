#include "SetChapterStateAction.h"
#include "../Manager/MainGameManager.h"
#include "../Script/Chapter.h"

USetChapterStateAction::USetChapterStateAction() :UActionBase()
{
	actionName = TEXT("SetChapterState");
}

void USetChapterStateAction::Load(FXmlNode* xmlNode)
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
	}
}

void USetChapterStateAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetChapterStateAction::ExecuteReal()
{
	if (isCurrent)
	{
		UChapter* currentChapter = UScriptManager::GetInstance()->GetCurrentChapter();
		if (currentChapter != nullptr)
		{
			chapter = currentChapter->GetChapterIndexName();
		}
	}
	UUserData* userData = UMainGameManager::GetInstance()->GetUserData();
	userData->SetChapterState(chapter, state);
	return FString();
}