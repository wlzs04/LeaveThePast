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

void USetSectionStateAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			state = FCString::Atoi(*attributeValue);
			break;
		case 2:
			chapter = attributeValue;
			isCurrent = false;
			break;
		case 3:
			sectionId = FCString::Atoi(*attributeValue);
			isCurrent = false;
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
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
		if (UScriptManager::GetInstance()->IsExecutingScript())
		{
			FScriptItemData scriptItemData = UScriptManager::GetInstance()->GetCurrentScriptItemData();
			chapter = scriptItemData.chapter;
			sectionId = scriptItemData.sectionId;
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
