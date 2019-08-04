#include "AddNextScriptAction.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/MainGameManager.h"
#include "../Config/UserData.h"
#include "../Manager/LogManager.h"

void UAddNextScriptAction::Load(FXmlNode* xmlNode)
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

void UAddNextScriptAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		chapterName = paramList[1];
	}
	if (paramList.Num() > 2)
	{
		sectionId = FCString::Atoi(*paramList[2]);
	}
	if (paramList.Num() > 3)
	{
		paragraphId = FCString::Atoi(*paramList[3]);
	}
}

void UAddNextScriptAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UAddNextScriptAction::ExecuteReal()
{
	UMainGameManager::GetInstance()->GetUserData()->AddNextScript(FScriptItemData(chapterName, sectionId, paragraphId));
	return FString();
}
