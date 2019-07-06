#include "DirectorActor.h"
#include "Components/InputComponent.h"
#include "../Manager/MainGameManager.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values
ADirectorActor::ADirectorActor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ADirectorActor::InitActorList()
{
	UMainGameManager* gameManager = (UMainGameManager*)(GWorld->GetGameInstance());
	UActorManager* actorManager = gameManager->GetActorManager();

	//将所有常驻演员加载到场景中
	actorManager->LoadAllPermanentActorToScene();

	AActorBase* mainActor = actorManager->LoadActorToSceneById(10001);
	AActorBase* mainActor2 = actorManager->LoadActorToSceneById(10002);

	canControlActorList.Add(mainActor);
	canControlActorList.Add(mainActor2);

	SetCameraActorById(10001);
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

// Called when the game starts or when spawned
void ADirectorActor::BeginPlay()
{
	Super::BeginPlay();
	//InitActorList();
}

// Called every frame
void ADirectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADirectorActor::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("MoveForward", this, &ADirectorActor::MoveForwardInputFunction);
	playerInputComponent->BindAxis("MoveRight", this, &ADirectorActor::MoveRightInputFunction);

	playerInputComponent->BindAxis("Turn", this, &ADirectorActor::TurnInputFunction);
	playerInputComponent->BindAxis("LookUp", this, &ADirectorActor::LookUpInputFunction);

	playerInputComponent->BindAction("ChangeControlActor",EInputEvent::IE_Released,this, &ADirectorActor::ChangeControlActorInputFunction);
}

void ADirectorActor::MoveForwardInputFunction(float value)
{
	if (currentControlActor != nullptr)
	{
		currentControlActor->MoveForwardInputFunction(value);
	}
}

void ADirectorActor::MoveRightInputFunction(float value)
{
	if (currentControlActor != nullptr)
	{
		currentControlActor->MoveRightInputFunction(value);
	}
}

void ADirectorActor::TurnInputFunction(float value)
{
	AddControllerYawInput(value * 45 * GetWorld()->GetDeltaSeconds());
}

void ADirectorActor::LookUpInputFunction(float value)
{
	AddControllerPitchInput(value * 45 * GetWorld()->GetDeltaSeconds());
}

void ADirectorActor::ChangeControlActorInputFunction()
{
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

