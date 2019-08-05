#include "ChatAction.h"
#include "../Actor/ActorBase.h"
#include "../Actor/DirectorActor.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/UIManager.h"
#include "Engine/World.h"

void UChatAction::Load(FXmlNode* xmlNode)
{
	for (auto attribute : xmlNode->GetAttributes())
	{
		FString attributeName = attribute.GetTag();
		FString attributeValue = attribute.GetValue();
		if (attributeName == TEXT("actorId"))
		{
			actorInfoId = FCString::Atoi(*attributeValue);
			isPlayerControlActorId = false;
		}
		else if (attributeName == TEXT("text"))
		{
			text = attributeValue;
		}
		else if (attributeName == TEXT("voicePath"))
		{
			voicePath = attributeValue;
		}
		else if (attributeName == TEXT("actionTime"))
		{
			actionTime = FCString::Atof(*attributeValue);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("%s指令中存在未知属性:%s：%s！"), *actionName, *attributeName, *attributeValue));
		}
	}
}

void UChatAction::Load(TArray<FString> paramList)
{
	for (int i = 1; i < paramList.Num(); i++)
	{
		FString attributeValue = paramList[i];
		switch (i)
		{
		case 1:
			actorInfoId = FCString::Atoi(*attributeValue);
			isPlayerControlActorId = false;
			break;
		case 2:
			text = attributeValue;
			break;
		case 3:
			voicePath = attributeValue;
			break;
		case 4:
			actionTime = FCString::Atof(*attributeValue);
			break;
		default:
			LogWarning(FString::Printf(TEXT("%s指令中没有第%d参数:%s！"), *actionName, i, *attributeValue));
			break;
		}
	}
}

void UChatAction::Update()
{
	if (isCompleted == false)
	{
		currentTime += UScriptManager::GetInstance()->GetScriptTickTime();
		if (currentTime < actionTime)
		{

		}
		else
		{
			Finish();
		}
	}
}

FString UChatAction::ExecuteReal()
{
	if (isPlayerControlActorId)
	{
		executeActor = ADirectorActor::GetInstance()->GetCurrentControlActor();
	}
	else
	{
		executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	}
	if (executeActor == nullptr)
	{
		LogError(FString::Printf(TEXT("指令：%s未找到actorInId：%d"), *actionName, actorInfoId));
	}
	else
	{
		UClass* chatUIBPClass = LoadObject<UClass>(NULL, TEXT("Blueprint'/Game/GameContent/WorldObject/UI/ChatUIBP.ChatUIBP_C'"));
		chatUIBP = GWorld->SpawnActor(chatUIBPClass);
		chatUIBP->AttachToActor(executeActor,FAttachmentTransformRules::KeepRelativeTransform);

		UFunction* functionSetInfo = chatUIBP->FindFunction(TEXT("SetText"));
		if (functionSetInfo)
		{
			chatUIBP->ProcessEvent(functionSetInfo, &text);
		}
		else
		{
			LogError(FString::Printf(TEXT("指令:%s没有方法SetText。"), *actionName));
		}
		chatUIBP->SetActorRelativeLocation(FVector(0, 0, 130));
		executeActor->StartTalk();
	}
	currentTime = 0;
	return FString();
}

void UChatAction::FinishReal()
{
	if (executeActor != nullptr)
	{
		chatUIBP->Destroy();
		executeActor->StopTalk();
		executeActor = nullptr;
	}
}
