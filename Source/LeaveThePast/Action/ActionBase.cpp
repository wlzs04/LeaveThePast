#include "ActionBase.h"
#include "../Actor/ActorBase.h"
#include "../Manager/MainGameManager.h"
#include "Engine/World.h"

void UActionBase::Init()
{
	isCompleted = false;
}

int UActionBase::GetActorId()
{
	return actorId;
}

FString UActionBase::GetActionName()
{
	return actionName;
}

void UActionBase::Execute()
{
	LogNormal(actionName + TEXT("指令开始执行！"));
	UMainGameManager* gameManager = UMainGameManager::GetInstance();
	executeActor = gameManager->GetActorManager()->GetActorById(actorId);
	ExecuteReal();
}

void UActionBase::Load(FXmlNode* xmlNode)
{
	for(auto item : xmlNode->GetAttributes())
	{
		if (item.GetTag() == "actorId")
		{
			actorId = FCString::Atoi(*item.GetValue());
		}
		else if (item.GetTag() == "isAsync")
		{
			isAsync = item.GetValue().ToBool();
		}
	}
}

void UActionBase::Load(TArray<FString> paramList)
{
	LogWarning(TEXT("指令：")+ actionName+TEXT("未完成Load(TArray<FString> paramList)方法"));
}

bool UActionBase::GetIsCompleted()
{
	return isCompleted;
}

AActorBase* UActionBase::GetExecuteActor()
{
	return executeActor;
}
