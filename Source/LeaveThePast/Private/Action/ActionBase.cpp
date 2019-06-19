#include "..\..\Public\Action\ActionBase.h"
#include "..\..\Public\Actor\ActorBase.h"
#include "..\..\Public\Manager\MainGameManager.h"
#include "Engine/World.h"

UActionBase::UActionBase():UObject()
{
	
}

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
	UE_LOG(LogLoad, Log, TEXT("%s指令开始执行！"), *actionName);
	UMainGameManager* gameManager = (UMainGameManager*)(GWorld->GetGameInstance());
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

bool UActionBase::GetIsCompleted()
{
	return isCompleted;
}

AActorBase* UActionBase::GetExecuteActor()
{
	return executeActor;
}
