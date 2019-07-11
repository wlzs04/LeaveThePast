#include "ActorBase.h"
#include "..\Action\ActionBase.h"
#include "..\Manager\LogManager.h"
#include "..\Manager\AudioManager.h"
#include "GameFramework/Controller.h"
#include "Engine/Engine.h"
#include "Sound/SoundBase.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "GameFramework/PlayerInput.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AActorBase::AActorBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	bFindCameraComponentWhenViewTarget = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	audioComponent->SetupAttachment(RootComponent);
	interactedComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Interacted"));
	interactedComponent->SetupAttachment(RootComponent);
	interactedComponent->SetSphereRadius(100);
}

void AActorBase::InitByActorInfo()
{
	LoadModel();
	Restart();
}

// Called when the game starts or when spawned
void AActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AActorBase::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
}

void AActorBase::MoveForwardInputFunction(float value)
{
	APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
	if ((playerController != NULL) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = playerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AActorBase::MoveRightInputFunction(float value)
{
	APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
	if ((playerController != NULL) && (value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = playerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void AActorBase::TurnInputFunction(float value)
{
	AddControllerYawInput(value * 45 * GetWorld()->GetDeltaSeconds());
}

void AActorBase::LookUpInputFunction(float value)
{
	AddControllerPitchInput(value * 45 * GetWorld()->GetDeltaSeconds());
}

void AActorBase::SetAccelerate(bool enableAccelerate)
{
	float newMaxWalkSpeed = actorInfo->GetPropertyValue(TEXT("Speed"));
	if (enableAccelerate)
	{
		newMaxWalkSpeed *= 6;
	}
	GetCharacterMovement()->MaxWalkSpeed = newMaxWalkSpeed;
}

TArray<AActor*> AActorBase::GetInteractedActor()
{
	TArray<AActor*> overlappingActorList;
	interactedComponent->GetOverlappingActors(overlappingActorList, AActorBase::StaticClass());
	return overlappingActorList;
}

// Called every frame
void AActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorBase::Execute(UActionBase* action)
{
	if (actionList.Contains(action))
	{
		LogError(FString::Printf(TEXT("演员Id:%d已经拥有指令:%s"), actorInfo->GetActorId(), *action->GetActionName()));
		return;
	}
	actionList.Add(action);
}

void AActorBase::StartPerform()
{
	
}

void AActorBase::SetActorInfo(UActorInfoBase* newActorInfo)
{
	actorInfo = newActorInfo;
	if (actorInfo == nullptr)
	{
		LogError(TEXT("设置actorinfo为空。"));
		return;
	}
	GetCharacterMovement()->MaxWalkSpeed =  actorInfo->GetPropertyValue(TEXT("Speed"));
	//audioComponent->SoundClassOverride = UAudioManager::GetInstance()->GetVoiceSoundClass();
}

UActorInfoBase* AActorBase::GetActorInfo()
{
	return actorInfo;
}

void AActorBase::LoadModel()
{
	if (actorInfo == nullptr)
	{
		return;
	}
	FString modelPath = actorInfo->GetModelRootPath();
	FString modelName = actorInfo->GetModelName();
	if (!modelPath.IsEmpty())
	{
		FString realModelPath = TEXT("SkeletalMesh'/Game/");
		realModelPath += modelPath + TEXT("/")+ modelName+ TEXT(".") + modelName + TEXT("'");
		USkeletalMesh* newMesh = LoadObject<USkeletalMesh>(NULL, realModelPath.GetCharArray().GetData());
		if (newMesh==nullptr)
		{
			LogError(FString::Printf(TEXT("演员Id:%d模型加载失败，路径：%s"), actorInfo->GetActorId(), *realModelPath));
		}
		else
		{
			GetMesh()->SetSkeletalMesh(newMesh);
		}
		//UAnimBlueprint
		FString realAnimationPath = TEXT("/Game/");
		realAnimationPath += modelPath + TEXT("/") + modelName + TEXT("AnimBP.") + modelName + TEXT("AnimBP_C");
		UAnimBlueprintGeneratedClass* meshAnim = LoadObject<UAnimBlueprintGeneratedClass>(NULL, realAnimationPath.GetCharArray().GetData());
		GetMesh()->SetAnimInstanceClass(meshAnim);
	}
	else
	{
		LogError(FString::Printf(TEXT("演员Id:%d模型路径为空"), actorInfo->GetActorId()));
	}
}

int AActorBase::GetActorId()
{
	return actorInfo->GetActorId();
}

FVector AActorBase::GetDefaultPosition()
{
	return actorInfo->GetDefaultPosition();
}

FRotator AActorBase::GetDefaultRotation()
{
	return actorInfo->GetDefaultRotation();
}

bool AActorBase::IsInTalking()
{
	return isInTalking;
}

void AActorBase::StartTalk()
{
	isInTalking = true;
}

void AActorBase::StopTalk()
{
	isInTalking = false;
}

void AActorBase::StartPlaySound(USoundBase* soundBase)
{
	audioComponent->SetSound(soundBase);
}

void AActorBase::AddCameraFollow()
{
	if (springArmComponent == nullptr)
	{
		springArmComponent = NewObject<USpringArmComponent>(this, TEXT("SpringArm"), RF_NoFlags, nullptr, false, nullptr);
		springArmComponent->SetupAttachment(RootComponent);
		springArmComponent->TargetArmLength = 300.0f;
		springArmComponent->bUsePawnControlRotation = true;
		springArmComponent->SetRelativeLocation(FVector(0, 0, 90));
		springArmComponent->RegisterComponent();
		AddInstanceComponent(springArmComponent);
	}
	if (cameraComponent == nullptr)
	{
		cameraComponent = NewObject<UCameraComponent>(this, TEXT("Camera"), RF_NoFlags, nullptr, false, nullptr);
		cameraComponent->SetupAttachment(springArmComponent, USpringArmComponent::SocketName);
		cameraComponent->bUsePawnControlRotation = false;
		cameraComponent->RegisterComponent();
		AddInstanceComponent(cameraComponent);
	}
}

void AActorBase::RemoveCameraFollow()
{
	if (springArmComponent != nullptr)
	{
		springArmComponent->UnregisterComponent();
		RemoveInstanceComponent(springArmComponent);
		springArmComponent->DestroyComponent();
		springArmComponent = nullptr;
	}
	if (cameraComponent != nullptr)
	{
		cameraComponent->UnregisterComponent();
		RemoveInstanceComponent(cameraComponent);
		cameraComponent->DestroyComponent();
		cameraComponent = nullptr;
	}
}
