#include "ChangeCameraActorAction.h"
#include "..\..\Public\Manager\MainGameManager.h"
#include "..\..\Public\Actor\DirectorActor.h"
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
	if (isCompleted == false && GetExecuteActor() != nullptr)
	{
		APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
		((ADirectorActor*)playerController->GetPawn())->SetCameraActorById(GetActorId());
		isCompleted = true;
	}
}

void UChangeCameraActorAction::ExecuteReal()
{
	isCompleted = false;
}
