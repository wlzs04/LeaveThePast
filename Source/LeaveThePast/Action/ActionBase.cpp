#include "ActionBase.h"
#include "../Actor/ActorBase.h"
#include "../Manager/MainGameManager.h"
#include "Engine/World.h"

void UActionBase::Init()
{
	isCompleted = false;
}

int UActionBase::GetActorInfoId()
{
	return actorInfoId;
}

FString UActionBase::GetActionName()
{
	return actionName;
}

FString UActionBase::Execute()
{
	LogNormal(actionName + TEXT("指令开始执行！"));
	executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	return ExecuteReal();
}

void UActionBase::Load(FXmlNode* xmlNode)
{
	for(auto item : xmlNode->GetAttributes())
	{
		if (item.GetTag() == "actorId")
		{
			actorInfoId = FCString::Atoi(*item.GetValue());
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
