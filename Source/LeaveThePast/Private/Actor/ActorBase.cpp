#include "ActorBase.h"
#include "..\..\Public\Action\ActionBase.h"
#include "GameFramework/Controller.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Runtime\Engine\Classes\Engine\InputDelegateBinding.h>

// Sets default values
AActorBase::AActorBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	//BaseTurnRate = 45.f;
	//BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//AutoPossessPlayer = EAutoReceiveInput::Player0;
	//AutoPossessPlayer = EAutoReceiveInput::Player0;
	bFindCameraComponentWhenViewTarget = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));

	//AddCameraFollow();
}

// Called when the game starts or when spawned
void AActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AActorBase::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	//check(playerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	
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
		// add movement in that direction
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

// Called every frame
void AActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorBase::Execute(UActionBase* action)
{
	if (actionList.Contains(action))
	{
		UE_LOG(LogLoad, Log, TEXT("演员Id:%d已经拥有指令:%s！"), actorInfo->GetActorId(), *action->GetActionName());
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
	LoadModel();
	GetCharacterMovement()->MaxWalkSpeed = FCString::Atof(*actorInfo->GetPropertyValue(TEXT("Speed")));
}

UActorInfoBase* AActorBase::GetActorInfo()
{
	return actorInfo;
}

void AActorBase::LoadModel()
{
	FString modelPath = actorInfo->GetModelRootPath();
	FString modelName = actorInfo->GetModelName();
	if (!modelPath.IsEmpty())
	{
		FString realModelPath = TEXT("SkeletalMesh'/Game/");
		realModelPath += modelPath + TEXT("/")+ modelName+ TEXT(".") + modelName + TEXT("'");
		USkeletalMesh* newMesh = LoadObject<USkeletalMesh>(NULL, realModelPath.GetCharArray().GetData());
		if (newMesh==nullptr)
		{
			UE_LOG(LogLoad, Log, TEXT("演员Id:%d模型加载失败，路径：%s"), actorInfo->GetActorId(), *modelName);
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
		UE_LOG(LogLoad, Log, TEXT("演员Id:%d模型路径为空"), actorInfo->GetActorId());
	}
}

int AActorBase::GetActorId()
{
	return actorInfo->GetActorId();
}

bool AActorBase::IsPermanent()
{
	return actorInfo->IsPermanent();
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

void AActorBase::AddInputFunction()
{
	// Set up player input component, if there isn't one already.
	//if (InputComponent == nullptr)
	//{
	//	InputComponent = CreatePlayerInputComponent();
	//	if (InputComponent)
	//	{
	//		SetupPlayerInputComponent(InputComponent);
	//		AddInstanceComponent(InputComponent);
	//		//InputComponent->RegisterComponent();
	//		if (UInputDelegateBinding::SupportsInputDelegate(GetClass()))
	//		{
	//			InputComponent->bBlockInput = bBlockInput;
	//			UInputDelegateBinding::BindInputDelegates(GetClass(), InputComponent);
	//		}

	//	}
	//}
}
