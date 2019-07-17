#include "DirectorActor.h"
#include "Components/InputComponent.h"
#include "../Manager/MainGameManager.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

ADirectorActor::ADirectorActor()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	audioComponent->SetupAttachment(RootComponent);
}

void ADirectorActor::InitActorList()
{
	UMainGameManager* gameManager = (UMainGameManager*)(GWorld->GetGameInstance());
	UActorManager* actorManager = gameManager->GetActorManager();

	AActorBase* mainActor = actorManager->LoadActorToSceneByActorInfo(actorManager->GetActorInfoByInfoId(10001));
	AActorBase* mainActor2 = actorManager->LoadActorToSceneByActorInfo(actorManager->GetActorInfoByInfoId(10002));

	canControlActorList.Add(mainActor);
	canControlActorList.Add(mainActor2);

	SetCameraActorById(mainActor->GetActorId());
}

void ADirectorActor::SetCameraActorById(int actorId)
{
	if (currentControlActor != nullptr && currentControlActor->GetActorId() == actorId)
	{
		return;
	}
	UMainGameManager* gameManager = (UMainGameManager*)(GWorld->GetGameInstance());
	UActorManager* actorManager = gameManager->GetActorManager();
	AActorBase* actor = actorManager->GetActorById(actorId);
	if (actor != nullptr)
	{
		if (currentControlActor != nullptr)
		{
			currentControlActor->RemoveCameraFollow();
		}
		currentControlActor = actor;
		currentControlActor->AddCameraFollow();

		APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
		playerController->SetViewTarget(currentControlActor);
		currentControlActor->Controller = playerController;
	}
	for (int i = 0; i < canControlActorList.Num(); i++)
	{
		if (canControlActorList[i]->GetActorId() == actorId)
		{
			currentControlActorIndex = i;
		}
	}
}

AActorBase* ADirectorActor::GetCameraActor()
{
	return currentControlActor;
}

void ADirectorActor::StartPlayBGMSound(USoundCue* soundBase)
{
	audioComponent->SetSound(soundBase);
	audioComponent->SoundClassOverride = UAudioManager::GetInstance()->GetBGMSoundClass();
	audioComponent->Play();
}

void  ADirectorActor::SetDestination(FVector newDestinationPosition)
{
	destinationPosition = newDestinationPosition;
}

FVector ADirectorActor::GetDestination()
{
	return destinationPosition;
}

void ADirectorActor::BeginPlay()
{
	Super::BeginPlay();
	GWorld->GetFirstPlayerController<APlayerController>()->bShowMouseCursor = true;
}

void ADirectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADirectorActor::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("MoveForward", this, &ADirectorActor::MoveForwardInputFunction);
	playerInputComponent->BindAxis("MoveRight", this, &ADirectorActor::MoveRightInputFunction);

	playerInputComponent->BindAxis("Turn", this, &ADirectorActor::TurnInputFunction);
	playerInputComponent->BindAxis("LookUp", this, &ADirectorActor::LookUpInputFunction);

	playerInputComponent->BindAction("ChangeControlActor", EInputEvent::IE_Released, this, &ADirectorActor::ChangeControlActorInputFunction);
	playerInputComponent->BindAction("System", EInputEvent::IE_Released, this, &ADirectorActor::SystemInputFunction);
	playerInputComponent->BindAction("Accelerate", EInputEvent::IE_Pressed, this, &ADirectorActor::StartAccelerateInputFunction);
	playerInputComponent->BindAction("Accelerate", EInputEvent::IE_Released, this, &ADirectorActor::StopAccelerateInputFunction);
	playerInputComponent->BindAction("Interacted", EInputEvent::IE_Pressed, this, &ADirectorActor::InteractedInputFunction);
	playerInputComponent->BindAction("Debug", EInputEvent::IE_Pressed, this, &ADirectorActor::DebugInputFunction);
	playerInputComponent->BindAction("Map", EInputEvent::IE_Pressed, this, &ADirectorActor::MapInputFunction);
	playerInputComponent->BindAction("Pause",EInputEvent::IE_Pressed,this, &ADirectorActor::PauseInputFunction);
}

void ADirectorActor::MoveForwardInputFunction(float value)
{
	if (inMenuUI || value == 0)
	{
		return;
	}
	if (currentControlActor != nullptr)
	{
		currentControlActor->MoveForwardInputFunction(value);
	}
}

void ADirectorActor::MoveRightInputFunction(float value)
{
	if (inMenuUI || value == 0)
	{
		return;
	}
	if (currentControlActor != nullptr)
	{
		currentControlActor->MoveRightInputFunction(value);
	}
}

void ADirectorActor::TurnInputFunction(float value)
{
	if (inMenuUI || value == 0)
	{
		return;
	}
	APlayerController* playerController = (APlayerController*)Controller;
	if (playerController->IsInputKeyDown(EKeys::RightMouseButton))
	{
		AddControllerYawInput(value * 45 * GetWorld()->GetDeltaSeconds());
	}
}

void ADirectorActor::LookUpInputFunction(float value)
{
	if (inMenuUI || value == 0)
	{
		return;
	}
	APlayerController* playerController = (APlayerController*)Controller;
	if (playerController->IsInputKeyDown(EKeys::RightMouseButton))
	{
		AddControllerPitchInput(value * 45 * GetWorld()->GetDeltaSeconds());
	}
}

void ADirectorActor::ChangeControlActorInputFunction()
{
	if (inMenuUI)
	{
		return;
	}
	if (canControlActorList.Num() == 0)
	{
		return;
	}
	currentControlActorIndex++;
	if (currentControlActorIndex >= canControlActorList.Num())
	{
		currentControlActorIndex = 0;
	}
	if (currentControlActor != nullptr)
	{
		currentControlActor->RemoveCameraFollow();
	}
	currentControlActor = canControlActorList[currentControlActorIndex];
	currentControlActor->AddCameraFollow();

	APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
	playerController->SetViewTarget(currentControlActor);
	currentControlActor->Controller = playerController;
}

void ADirectorActor::SystemInputFunction()
{
	if (inMenuUI)
	{
		inMenuUI = false;
		UUIManager::GetInstance()->HideMenuUI();
	}
	else
	{
		inMenuUI = true;
		UUIManager::GetInstance()->ShowMenuUI();
	}
}

void ADirectorActor::StartAccelerateInputFunction()
{
	if (currentControlActor != nullptr)
	{
		currentControlActor->SetAccelerate(true);
	}
}

void ADirectorActor::StopAccelerateInputFunction()
{
	if (currentControlActor != nullptr)
	{
		currentControlActor->SetAccelerate(false);
	}
}

void ADirectorActor::InteractedInputFunction()
{
	if (currentControlActor != nullptr)
	{
		TArray<AActor*> canInteractedActorList = currentControlActor->GetInteractedActor();
		for (AActor* actor : canInteractedActorList)
		{
			if (actor == currentControlActor)
			{
				continue;
			}
			AActorBase* actorBase = (AActorBase*)actor;
			if (actorBase != nullptr)
			{
				UActorInfoBase* actorInfo = actorBase->GetActorInfo();
				LogNormal(FString::FromInt(actorInfo->GetActorType()));
				if (actorInfo->GetActorType()==0)
				{
					FChat chat = actorInfo->GetRandomChat();
					if (!chat.text.IsEmpty())
					{
						UUIManager::GetInstance()->ShowTalkUI(chat.text, actorInfo->GetActorName(), 1, actorInfo->GetHeadImagePath());
					}
				}
				else if (actorInfo->GetActorType() == 1)
				{
					FString configName = actorInfo->GetActorTypeValue();
					UUIManager::GetInstance()->ShowShopUI(configName);
				}
				else
				{

				}
				break;
			}
		}
	}
}

void ADirectorActor::DebugInputFunction()
{
	if (inDebugUI)
	{
		inDebugUI = false;
		UUIManager::GetInstance()->HideDebugUI();
	}
	else
	{
		inDebugUI = true;
		UUIManager::GetInstance()->ShowDebugUI();
	}
}

void ADirectorActor::MapInputFunction()
{
	if (inMapUI)
	{
		inMapUI = false;
		UUIManager::GetInstance()->HideMapUI();
	}
	else
	{
		inMapUI = true;
		UUIManager::GetInstance()->ShowMapUI();
	}
}

void ADirectorActor::PauseInputFunction()
{
	if (inPauseUI)
	{
		inPauseUI = false;
		UUIManager::GetInstance()->HidePauseUI();
	}
	else
	{
		inPauseUI = true;
		UUIManager::GetInstance()->ShowPauseUI();
	}
}
