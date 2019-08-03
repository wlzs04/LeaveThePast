#include "SetChapterStateAction.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/LogManager.h"
#include "../Config/UserData.h"
#include "../Script/Chapter.h"

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
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
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
		if (UScriptManager::GetInstance()->IsExecutingScript())
		{
			chapter = UScriptManager::GetInstance()->GetCurrentScriptItemData().chapter;
		}
		else
		{
			LogError(FString::Printf(TEXT("指令:%s没有设置具体章信息，或当前没有正在运行的剧本，不能自动设置为当前。"), *actionName));
		}
	}
	UUserData* userData = UMainGameManager::GetInstance()->GetUserData();
	userData->SetChapterState(chapter, state);
	return FString();
}