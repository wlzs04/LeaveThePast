#include "ChangeCameraActorAction.h"
#include "..\Manager\MainGameManager.h"
#include "..\Actor\DirectorActor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


UChangeCameraActorAction::UChangeCameraActorAction()
{
	actionName = TEXT("ChangeCameraActor");
}

void UChangeCameraActorAction::Load(FXmlNode* xmlNode)
{
	UActionBase::Load(xmlNode);
}

void UChangeCameraActorAction::Update()
{
	if (isCompleted == false)
	{
		Finish();
	}
}

FString UChangeCameraActorAction::ExecuteReal()
{
	isCompleted = false;
	ADirectorActor::GetInstance()->SetControlActorById(GetExecuteActor()->GetActorId());
	return FString();
}
