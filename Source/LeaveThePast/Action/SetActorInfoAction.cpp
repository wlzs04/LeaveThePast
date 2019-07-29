#include "SetActorInfoAction.h"
#include "../Manager/ActorManager.h"
#include "../Manager/LogManager.h"

USetActorInfoAction::USetActorInfoAction() :UActionBase()
{
	actionName = TEXT("SetActorInfo");
}

void USetActorInfoAction::Load(FXmlNode* xmlNode)
{
	sceneActorInfo.LoadFromXmlNode(xmlNode);
}

void USetActorInfoAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString USetActorInfoAction::ExecuteReal()
{
	if (sceneActorInfo.needReplaceActorName)
	{
		UActorManager::GetInstance()->GetActorByInfoId(sceneActorInfo.actorId)->GetActorInfo()->SetActorName(sceneActorInfo.actorName);
	}
	if (sceneActorInfo.needReplacePosition)
	{
		UActorManager::GetInstance()->GetActorByInfoId(sceneActorInfo.actorId)->SetActorLocation(sceneActorInfo.position);
	}
	if (sceneActorInfo.needReplaceRotation)
	{
		UActorManager::GetInstance()->GetActorByInfoId(sceneActorInfo.actorId)->SetActorRotation(sceneActorInfo.rotation);
	}
	return FString();
}
