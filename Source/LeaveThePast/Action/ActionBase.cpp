#include "ActionBase.h"
#include "../Actor/ActorBase.h"
#include "../Manager/MainGameManager.h"
#include "Engine/World.h"

void UActionBase::Init()
{
	isCompleted = false;
}

FString UActionBase::GetActionName()
{
	return actionName;
}

FString UActionBase::Execute()
{
	isStart = true;
	isCompleted = false;
	LogNormal(actionName + TEXT("指令开始执行！"));
	//executeActor = UActorManager::GetInstance()->GetActorByInfoId(actorInfoId);
	return ExecuteReal();
}

void UActionBase::Finish()
{
	isStart = false;
	isCompleted = true;
}

void UActionBase::Load(FXmlNode* xmlNode)
{
	LogWarning(TEXT("指令：") + actionName + TEXT("无法从Xml中加载信息，需要重写加载方法。"));
}

void UActionBase::Load(TArray<FString> paramList)
{
	LogWarning(TEXT("指令：") + actionName + TEXT("无法从String中加载信息，需要重写加载方法。"));
}

bool UActionBase::GetIsCompleted()
{
	return isCompleted;
}

bool UActionBase::SkipAction()
{
	if (!isStart)
	{
		Execute();
	}
	Finish();
	return true;
}
