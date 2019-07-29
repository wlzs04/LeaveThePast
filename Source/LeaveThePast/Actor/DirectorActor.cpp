#include "DirectorActor.h"
#include "Components/InputComponent.h"
#include "../Manager/MainGameManager.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

ADirectorActor* ADirectorActor::directorActor = nullptr;

ADirectorActor::ADirectorActor()
{
	ADirectorActor::directorActor = this;

	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	interactedComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Interacted"));
	interactedComponent->SetSphereRadius(10); 
	RootComponent = interactedComponent;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	audioComponent->SetupAttachment(RootComponent);
}

ADirectorActor* ADirectorActor::GetInstance()
{
	return directorActor;
}

void ADirectorActor::InitActor()
{
	UMainGameManager* gameManager = UMainGameManager::GetInstance();
	UActorManager* actorManager = gameManager->GetActorManager();
	TArray<FSaveActorInfo> saveActorList = gameManager->GetUserData()->GetSceneActorList();

	for (FSaveActorInfo saveActorInfo: saveActorList)
	{
		if (actorManager->GetActorByInfoId(saveActorInfo.actorId) == nullptr)
		{
			UActorInfoBase* actorInfo = actorManager->GetNewActorInfoByInfoId(saveActorInfo.actorId);
			if (actorInfo != nullptr)
			{
				actorInfo->CoverData(saveActorInfo);
				AActorBase* actor = actorManager->LoadActorToSceneByActorInfo(actorInfo);
				for (FScriptRecorderInfo scriptRecorderInfo : saveActorInfo.scriptRecorderList)
				{
					actor->AddInteractedScript(scriptRecorderInfo);
				}
			}
		}
	}

	TArray<int> canControlActorSaveList = gameManager->GetUserData()->GetCanControlActorList();
	for (int canControlActorSaveActorInfoId : canControlActorSaveList)
	{
		AActorBase* actor = actorManager->GetActorByInfoId(canControlActorSaveActorInfoId);
		if (actor != nullptr)
		{
			canControlActorList.Add(actor);
		}
		else
		{
			LogError(FString::Printf(TEXT("初始化可控演员时未找到actorInfoId：%d"), canControlActorSaveActorInfoId));
		}
	}
	if (canControlActorList.Num() > 0)
	{
		SetControlActor(canControlActorList[0]);
	}

	TArray<FSaveVolumeInfo> saveVolumeList = gameManager->GetUserData()->GetSceneVolumeList();

	for (FSaveVolumeInfo saveVolumeInfo : saveVolumeList)
	{
		AVolumeBase* volume = actorManager->AddVolumeToSceneByVolumeInfo(saveVolumeInfo.volumeType, saveVolumeInfo.position);
		if (volume != nullptr)
		{
			volume->LoadFromString(saveVolumeInfo.value);
		}
	}
}

void ADirectorActor::AddCanControlActorByInfoId(int actorInfoId)
{
	UActorManager* actorManager = UActorManager::GetInstance();
	AActorBase* actor = actorManager->GetActorByInfoId(actorInfoId);
	if (actor == nullptr)
	{
		LogError(FString::Printf(TEXT("指令AddCanControlActor，未找到actorInfoId：%d"), actorInfoId));
	}
	else
	{
		if (!canControlActorList.Contains(actor))
		{
			canControlActorList.Add(actor);
		}
	}
}

void ADirectorActor::RemoveCanControlActorByInfoId(int actorInfoId)
{
	for (AActorBase* actor: canControlActorList)
	{
		if (actor->GetActorInfo()->GetActorId() == actorInfoId)
		{
			canControlActorList.Remove(actor);
			return;
		}
	}
}

void ADirectorActor::SetControlActorById(int actorId)
{
	if (currentControlActor != nullptr && currentControlActor->GetActorInfo()->GetActorId() == actorId)
	{
		return;
	}
	UMainGameManager* gameManager = UMainGameManager::GetInstance();
	UActorManager* actorManager = gameManager->GetActorManager();
	AActorBase* actor = actorManager->GetActorByInfoId(actorId);
	SetControlActor(actor);
}

void ADirectorActor::SetControlActor(AActorBase* actor)
{
	if (actor != nullptr)
	{
		if (currentControlActor != nullptr && currentControlActor->GetActorInfo()->GetActorId() == actor->GetActorInfo()->GetActorId())
		{
			return;
		}
		if (currentControlActor != nullptr)
		{
			currentControlActor->RemoveCameraFollow();
		}
		currentControlActor = actor;
		currentControlActor->AddCameraFollow();
		FAttachmentTransformRules attachmentTransform(EAttachmentRule::KeepRelative,true);
		AttachToActor(currentControlActor, attachmentTransform);
		SetActorRelativeLocation(FVector(0,0,0));
		APlayerController* playerController = UMainGameManager::GetInstance()->GetGameWorld()->GetFirstPlayerController<APlayerController>();
		playerController->SetViewTarget(currentControlActor);
		currentControlActor->Controller = playerController;
	}
	for (int i = 0; i < canControlActorList.Num(); i++)
	{
		if (canControlActorList[i]->GetActorInfo()->GetActorId() == actor->GetActorInfo()->GetActorId())
		{
			currentControlActorIndex = i;
		}
	}
}

AActorBase* ADirectorActor::GetControlActor()
{
	return currentControlActor;
}

TArray<AActorBase*> ADirectorActor::GetCanControlActorList()
{
	return canControlActorList;
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

bool ADirectorActor::GetCanControl()
{
	return canControl;
}

void ADirectorActor::SetCanControl(bool newCanControl)
{
	canControl = newCanControl;
}

void ADirectorActor::SetCanControlMove(bool newCanControlMove)
{
	canControlMove = newCanControlMove;
}

void ADirectorActor::SetCanControlView(bool newCanControlView)
{
	canControlView = newCanControlView;
}

void ADirectorActor::AddCanOnlyControlUINumber()
{
	canOnlyControlUINumber++;
}

void ADirectorActor::RemoveCanOnlyControlUINumber()
{
	canOnlyControlUINumber--;
	if (canOnlyControlUINumber<0)
	{
		LogError(TEXT("RemoveCanOnlyControlUINumber小于0"));
	}
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
	playerInputComponent->BindAction("Accelerate", EInputEvent::IE_Pressed, this, &ADirectorActor::StartAccelerateInputFunction);
	playerInputComponent->BindAction("Accelerate", EInputEvent::IE_Released, this, &ADirectorActor::StopAccelerateInputFunction);
	playerInputComponent->BindAction("Interacted", EInputEvent::IE_Pressed, this, &ADirectorActor::InteractedInputFunction);

	playerInputComponent->BindAction("System", EInputEvent::IE_Released, this, &ADirectorActor::SystemInputFunction);
	playerInputComponent->BindAction("Debug", EInputEvent::IE_Pressed, this, &ADirectorActor::DebugInputFunction);
	playerInputComponent->BindAction("Map", EInputEvent::IE_Pressed, this, &ADirectorActor::MapInputFunction);
}

void ADirectorActor::MoveForwardInputFunction(float value)
{
	if (!canControl || !canControlMove || canOnlyControlUINumber > 0 || value == 0)
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
	if (!canControl || !canControlMove || canOnlyControlUINumber > 0 || value == 0)
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
	if (!canControl || !canControlView || canOnlyControlUINumber > 0 || value == 0)
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
	if (!canControl || !canControlView || canOnlyControlUINumber > 0 || value == 0)
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
	if (!canControl || canOnlyControlUINumber > 0 || canControlActorList.Num() == 0)
	{
		return;
	}
	currentControlActorIndex++;
	if (currentControlActorIndex >= canControlActorList.Num())
	{
		currentControlActorIndex = 0;
	}
	SetControlActor(canControlActorList[currentControlActorIndex]);
}

void ADirectorActor::InteractedInputFunction()
{
	if (!canControl || canOnlyControlUINumber > 0)
	{
		return;
	}
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
				//先判断是否有需要执行的剧本
				if (actorBase->GetInteractedScriptList().Num() != 0)
				{
					FScriptRecorderInfo scriptRecorderInfo = actorBase->GetInteractedScriptList()[0];
					UScriptManager::GetInstance()->StartScript(scriptRecorderInfo.chapter, scriptRecorderInfo.sectionId, scriptRecorderInfo.paragraphId);
					return;
				}
				UActorInfoBase* actorInfo = actorBase->GetActorInfo();
				LogNormal(FString::Printf(TEXT("演员%d，类型%d。"), actorInfo->GetActorId(), actorInfo->GetActorType()));
				if (actorInfo->GetActorType() == 0)
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

void ADirectorActor::StartAccelerateInputFunction()
{
	if (!canControl || canOnlyControlUINumber > 0)
	{
		return;
	}
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

void ADirectorActor::SystemInputFunction()
{
	if (UScriptManager::GetInstance()->IsInScript())
	{
		if (UUIManager::GetInstance()->IsShowPauseUI())
		{
			UUIManager::GetInstance()->HidePauseUI();
		}
		else
		{
			if (canOnlyControlUINumber > 0)
			{
				return;
			}
			UUIManager::GetInstance()->ShowPauseUI();
		}
	}
	else
	{
		if (UUIManager::GetInstance()->IsShowMenuUI())
		{
			UUIManager::GetInstance()->HideMenuUI();
		}
		else
		{
			if (canOnlyControlUINumber > 0)
			{
				return;
			}
			UUIManager::GetInstance()->ShowMenuUI();
		}
	}
}

void ADirectorActor::DebugInputFunction()
{
	if (UUIManager::GetInstance()->IsShowDebugUI())
	{
		UUIManager::GetInstance()->HideDebugUI();
	}
	else
	{
		if (canOnlyControlUINumber > 0)
		{
			return;
		}
		UUIManager::GetInstance()->ShowDebugUI();
	}
}

void ADirectorActor::MapInputFunction()
{
	if (UUIManager::GetInstance()->IsShowMapUI())
	{
		UUIManager::GetInstance()->HideMapUI();
	}
	else
	{
		if (canOnlyControlUINumber > 0)
		{
			return;
		}
		UUIManager::GetInstance()->ShowMapUI();
	}
}
