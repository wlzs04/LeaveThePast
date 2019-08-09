#include "DirectorActor.h"
#include "Components/InputComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "../Manager/MainGameManager.h"
#include "../Manager/LogManager.h"
#include "../Manager/ActorManager.h"
#include "../Manager/AudioManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/UIManager.h"
#include "../Volume/VolumeBase.h"
#include "../Config/SceneData.h"
#include "ActorBase.h"
#include "MainAIController.h"
#include "Sound/SoundCue.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "XmlParser/Public/XmlFile.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"

ADirectorActor* ADirectorActor::directorActor = nullptr;

ADirectorActor::ADirectorActor()
{
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
	UUserData* userData = gameManager->GetUserData();
	TArray<USceneActorData*> sceneActorList = userData->GetSceneActorList();

	for (USceneActorData* sceneActorInfo: sceneActorList)
	{
		if (actorManager->GetActorByInfoId(sceneActorInfo->actorId) == nullptr)
		{
			UActorInfoBase* actorInfo = actorManager->GetNewActorInfoByInfoId(sceneActorInfo->actorId);
			if (actorInfo != nullptr)
			{
				actorInfo->CoverData(sceneActorInfo);
				AActorBase* actor = actorManager->LoadActorToSceneByActorInfo(actorInfo);
				for (FScriptItemData scriptItemData : sceneActorInfo->scriptItemDataList)
				{
					actor->AddInteractedScript(scriptItemData);
				}
			}
			else
			{
				LogError(FString::Printf(TEXT("初始化存档中场景演员时未找到actorId：%d"), sceneActorInfo->actorId));
			}
		}
	}

	TArray<int> canControlActorSaveList = userData->GetCanControlActorList();
	canControlActorList.Empty();
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
	SetControlActorByIndex(userData->GetCurrentControlActorIndex());
	
	for (size_t i = 0; i < canControlActorList.Num(); i++)
	{
		if (canControlActorList[i] != currentControlActor)
		{
			canControlActorList[i]->AddControlByAI();
		}
	}

	TArray<USceneVolumeData*> sceneVolumeList = userData->GetSceneVolumeList();

	for (USceneVolumeData* sceneVolumeInfo : sceneVolumeList)
	{
		AVolumeBase* volume = actorManager->AddVolumeToSceneByVolumeInfo(sceneVolumeInfo->volumeType, sceneVolumeInfo->position);
		if (volume != nullptr)
		{
			volume->LoadFromString(sceneVolumeInfo->value);
		}
		else 
		{
			LogError(FString::Printf(TEXT("初始化存档中场景体积时失败，类型:%s。"), *sceneVolumeInfo->volumeType));
		}
	}
}

void ADirectorActor::AddCanControlActorByInfoId(int actorInfoId)
{
	UActorManager* actorManager = UActorManager::GetInstance();
	AActorBase* actor = actorManager->GetActorByInfoId(actorInfoId);
	if (actor == nullptr)
	{
		LogError(FString::Printf(TEXT("添加可控演员时，未找到actorInfoId：%d"), actorInfoId));
	}
	else
	{
		if (!canControlActorList.Contains(actor))
		{
			canControlActorList.Add(actor);
		}
		else
		{
			LogWarning(FString::Printf(TEXT("此演员本是可控演员actorInfoId：%d"), actorInfoId));
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
	LogWarning(FString::Printf(TEXT("此演员本不是可控演员actorInfoId：%d"), actorInfoId));
}

void ADirectorActor::SetControlActorById(int actorId)
{
	if (currentControlActor != nullptr && currentControlActor->GetActorInfo()->GetActorId() == actorId)
	{
		return;
	}
	AActorBase* actor = UActorManager::GetInstance()->GetActorByInfoId(actorId);
	SetControlActor(actor);
}

void ADirectorActor::SetControlActorByIndex(int index)
{
	if (index>=0 && index< canControlActorList.Num())
	{
		SetControlActor(canControlActorList[index]);
	}
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
			currentControlActor->AddControlByAI();
		}
		currentControlActor = actor;
		currentControlActor->AddCameraFollow(); 
		currentControlActor->RemoveControlByAI();
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
		else if ((AMainAIController*)(canControlActorList[i]->Controller!=nullptr))
		{
			((AMainAIController*)(canControlActorList[i]->Controller))->SetTagetActor(currentControlActor);
		}
	}
}

AActorBase* ADirectorActor::GetCurrentControlActor()
{
	return currentControlActor;
}

int ADirectorActor::GetCurrentControlActorIndex()
{
	return currentControlActorIndex;
}

TArray<AActorBase*> ADirectorActor::GetCanControlActorList()
{
	return canControlActorList;
}

void ADirectorActor::StartPlayBGMSound(USoundCue* soundBase)
{
	if (soundBase==nullptr)
	{
		LogError(TEXT("Director在设置BGM时传入值为空。"));
		return;
	}
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

	ADirectorActor::directorActor = this;
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
					FScriptItemData scriptItemData = actorBase->GetInteractedScriptList()[0];
					UScriptManager::GetInstance()->StartScript(scriptItemData.chapter, scriptItemData.sectionId, scriptItemData.paragraphId);
					return;
				}
				if (actorBase->GetActorInfo()->GetInteractParagraph()!=nullptr)
				{
					UScriptManager::GetInstance()->ExecuteParagraph(actorBase->GetActorInfo()->GetInteractParagraph());
					break;
				}
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
	if (UScriptManager::GetInstance()->IsExecutingScript())
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
