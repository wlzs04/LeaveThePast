#include "RemoveNextScriptAction.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/MainGameManager.h"
#include "../Config/UserData.h"
#include "../Manager/LogManager.h"

void URemoveNextScriptAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("chapter"))
		{
			chapterName = attributeValue;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			sectionId = FCString::Atoi(*attributeValue);
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			paragraphId = FCString::Atoi(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void URemoveNextScriptAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			chapterName = attributeValue;
		case 2:
			sectionId = FCString::Atoi(*attributeValue);
		case 3:
			paragraphId = FCString::Atoi(*attributeValue);
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void URemoveNextScriptAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveNextScriptAction::ExecuteReal()
{
	UMainGameManager::GetInstance()->GetUserData()->RemoveNextScript(FScriptItemData(chapterName, sectionId, paragraphId));
	return FString();
}