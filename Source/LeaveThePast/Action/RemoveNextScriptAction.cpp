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