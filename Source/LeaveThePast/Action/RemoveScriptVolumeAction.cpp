#include "RemoveScriptVolumeAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/MainGameManager.h"
#include "../Script/Chapter.h"
#include "../Script/Section.h"
#include "../Script/Paragraph.h"
#include "../Volume/ScriptVolume.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "Engine/Public/EngineUtils.h"

void URemoveScriptVolumeAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("chapter"))
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

void URemoveScriptVolumeAction::Load(TArray<FString> paramList)
{
	if (paramList.Num() > 1)
	{
		scriptItemData.chapter = paramList[1];
		isCurrent = false;
	}
	if (paramList.Num() > 2)
	{
		scriptItemData.sectionId = FCString::Atoi(*paramList[2]);
		isCurrent = false;
	}
	if (paramList.Num() > 3)
	{
		scriptItemData.paragraphId = FCString::Atoi(*paramList[3]);
		isCurrent = false;
	}
}

void URemoveScriptVolumeAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString URemoveScriptVolumeAction::ExecuteReal()
{
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
	FString volumeValue; 
	volumeValue.Append(scriptItemData.chapter + TEXT(" "));
	volumeValue.Append(FString::FromInt(scriptItemData.sectionId) + TEXT(" "));
	volumeValue.Append(FString::FromInt(scriptItemData.paragraphId));
	UActorManager::GetInstance()->RemoveVolumeByVolumeValue(volumeValue);

	return FString();
}
