#include "Paragraph.h"
#include "../Manager/MainGameManager.h"
#include "../Actor/DirectorActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void UParagraph::Update()
{
	if (isStart)
	{
		if (currentActionIndex >= actionList.Num())
		{
			isStart = false;
			isCompleted = true;
			return;
		}
		if (!actionList[currentActionIndex]->GetIsCompleted())
		{
			actionList[currentActionIndex]->Update();
			return;
		}
		else
		{
			currentActionIndex++;
			if (currentActionIndex >= actionList.Num())
			{
				isStart = false;
				isCompleted = true;

				APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
				((ADirectorActor*)playerController->GetPawn())->EnableInput(playerController);

				return;
			}
			actionList[currentActionIndex]->Execute();
			return;
		}
	}
}

void UParagraph::Load(FXmlNode* xmlNode)
{
	UMainGameManager* gameManager = ((UMainGameManager*)(GWorld->GetGameInstance()));
	for (auto childNode : xmlNode->GetChildrenNodes())
	{
		UActionBase* actionBase = gameManager->GetIegalActionByName(childNode->GetTag());

		if (actionBase != nullptr)
		{
			UActionBase* actionBase2 = NewObject<UActionBase>((UObject*)GetTransientPackage(), actionBase->GetClass());
			actionBase2->Load(childNode);
			actionList.Add(actionBase2);
		}
		else
		{
			UE_LOG(LogLoad, Error, TEXT("未知指令：%s"), *childNode->GetTag());
		}
	}
}

bool UParagraph::GetIsCompleted()
{
	return isCompleted;
}

void UParagraph::Start()
{
	currentActionIndex = 0;
	isStart = true;
	isCompleted = false;

	APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
	((ADirectorActor*)playerController->GetPawn())->DisableInput(playerController);

	actionList[currentActionIndex]->Execute();
}