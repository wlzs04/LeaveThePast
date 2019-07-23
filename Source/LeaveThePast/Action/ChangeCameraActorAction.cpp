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
		APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
		
		((ADirectorActor*)playerController->GetPawn())->SetControlActorById(GetExecuteActor()->GetActorId());
		isCompleted = true;
	}
}

FString UChangeCameraActorAction::ExecuteReal()
{
	isCompleted = false;
	return FString();
}
