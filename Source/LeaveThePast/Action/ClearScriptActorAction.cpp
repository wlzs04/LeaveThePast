#include "ClearScriptActorAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Actor/ActorBase.h"
#include "../Script/Chapter.h"
#include "../Script/Section.h"
#include "../Script/Paragraph.h"

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
			scriptItemData.chapter = attributeValue;
			isCurrent = false;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			scriptItemData.sectionId = FCString::Atoi(*attributeValue);
			isCurrent = false;
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			scriptItemData.paragraphId = FCString::Atoi(*attributeValue);
			isCurrent = false;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UClearScriptActorAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			actorInfoId = FCString::Atoi(*attributeValue);
			break;
		case 2:
			scriptItemData.chapter = attributeValue;
			isCurrent = false;
			break;
		case 3:
			scriptItemData.sectionId = FCString::Atoi(*attributeValue);
			isCurrent = false;
			break;
		case 4:
			scriptItemData.paragraphId = FCString::Atoi(*attributeValue);
			isCurrent = false;
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
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
		LogError(FString::Printf(TEXT("指令：%s，场景中不存在演员：%d"),*actionName, actorInfoId));
		return FString();
	}
	if (isCurrent)
	{
		if (UScriptManager::GetInstance()->IsExecutingScript())
		{
			scriptItemData = UScriptManager::GetInstance()->GetCurrentScriptItemData();
		}
		else
		{
			LogError(FString::Printf(TEXT("指令:%s没有设置具体章节信息，或当前没有正在运行的剧本，不能自动设置为当前。"), *actionName));
		}
	}
	actor->RemoveInteractedScript(scriptItemData);

	return FString();
}