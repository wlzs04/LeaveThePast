#include "SetSectionStateAction.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"
#include "../Script/Chapter.h"
#include "../Script/Section.h"
#include "../Config/UserData.h"

void USetSectionStateAction::Load(FXmlNode* xmlNode)
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
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void USetSectionStateAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetSectionStateAction::ExecuteReal()
{
	if (isCurrent)
	{
		UChapter* currentChapter = UScriptManager::GetInstance()->GetCurrentChapter();
		if (currentChapter != nullptr)
		{
			chapter = currentChapter->GetChapterIndexName();
			sectionId = currentChapter->GetCurrentSection()->GetSectionId();
		}
		else
		{
			LogError(FString::Printf(TEXT("指令:%s没有设置具体章节信息，或当前没有正在运行的剧本，不能自动设置为当前。"), *actionName));
		}
	}
	UUserData* userData = UMainGameManager::GetInstance()->GetUserData();
	userData->SetSectionState(chapter,sectionId, state);
	return FString();
}
