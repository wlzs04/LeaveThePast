#include "AddScriptVolumeAction.h"
#include "../Manager/HelpManager.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Script/Chapter.h"
#include "../Script/Section.h"
#include "../Script/Paragraph.h"
#include "../Volume/ScriptVolume.h"
#include "../LeaveThePastGameModeBase.h"

void UAddScriptVolumeAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("position"))
		{
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
		}
		else if (attributeName == TEXT("chapter"))
		{
			scriptItemData.chapter = attributeValue;
			isNext = false;
		}
		else if (attributeName == TEXT("sectionId"))
		{
			scriptItemData.sectionId = FCString::Atoi(*attributeValue);
			isNext = false;
		}
		else if (attributeName == TEXT("paragraphId"))
		{
			scriptItemData.paragraphId = FCString::Atoi(*attributeValue);
			isNext = false;
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UAddScriptVolumeAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			position = UHelpManager::ConvertFStringToFVector(attributeValue);
			break;
		case 2:
			scriptItemData.chapter = attributeValue;
			isNext = false;
			break;
		case 3:
			scriptItemData.sectionId = FCString::Atoi(*attributeValue);
			isNext = false;
			break;
		case 4:
			scriptItemData.paragraphId = FCString::Atoi(*attributeValue);
			isNext = false;
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void UAddScriptVolumeAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UAddScriptVolumeAction::ExecuteReal()
{
	AScriptVolume* scriptVolume = (AScriptVolume*)UActorManager::GetInstance()->AddVolumeToSceneByVolumeInfo(TEXT("Script"), position);
	
	if (isNext)
	{
		if (UScriptManager::GetInstance()->IsExecutingScript())
		{
			scriptItemData = UScriptManager::GetInstance()->GetCurrentScriptItemData();
			scriptItemData.paragraphId = scriptItemData.paragraphId + 1;
		}
		else
		{
			LogError(FString::Printf(TEXT("指令:%s没有设置具体章节信息，或当前没有正在运行的剧本，不能自动设置为下一个。"), *actionName));
		}
	}

	scriptVolume->SetInfo(scriptItemData);
	return FString();
}