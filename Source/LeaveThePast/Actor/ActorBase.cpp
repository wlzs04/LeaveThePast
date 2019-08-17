#include "ActorBase.h"
#include "../Action/ActionBase.h"
#include "DirectorActor.h"
#include "MainAIController.h"
#include "../Manager/LogManager.h"
#include "../Manager/AudioManager.h"
#include "../Manager/ScriptManager.h"
#include "../Manager/MainGameManager.h"
#include "../Config/UserData.h"
#include "../Config/KeySkillMapData.h"
#include "../Script/Paragraph.h"
#include "../Skill/SkillBase.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardData.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"

AActorBase::AActorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 150;

	bFindCameraComponentWhenViewTarget = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, 90, 0));

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	audioComponent->SetupAttachment(RootComponent);

	interactComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Interact"));
	interactComponent->SetupAttachment(RootComponent);
	interactComponent->SetSphereRadius(100);

	nearbyComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Nearby"));
	nearbyComponent->SetupAttachment(RootComponent);
	nearbyComponent->SetSphereRadius(200);

	nearbyComponent->OnComponentBeginOverlap.AddDynamic(this, &AActorBase::ActorBeginOverlapEvent);
	nearbyComponent->OnComponentEndOverlap.AddDynamic(this, &AActorBase::ActorEndOverlapEvent);
}

void AActorBase::InitByActorInfo()
{
	LoadModel();
	Restart();
}

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
	/*if (isInAttack)
	{
		return;
	}*/
	APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
	if ((playerController != NULL) && (value != 0.0f))
	{
		const FRotator Rotation = playerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AActorBase::MoveRightInputFunction(float value)
{
	/*if (isInAttack)
	{
		return;
	}*/
	APlayerController* playerController = GWorld->GetFirstPlayerController<APlayerController>();
	if ((playerController != NULL) && (value != 0.0f))
	{
		const FRotator Rotation = playerController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

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
	if (enableAccelerate)
	{
		float newMaxWalkSpeed = actorInfo->GetPropertyValue(TEXT("Speed"));
		GetCharacterMovement()->MaxWalkSpeed = newMaxWalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 150;
	}
}

TArray<AActor*> AActorBase::GetInteractedActor()
{
	TArray<AActor*> overlappingActorList;
	interactComponent->GetOverlappingActors(overlappingActorList, AActorBase::StaticClass());
	return overlappingActorList;
}

TArray<FScriptItemData> AActorBase::GetInteractedScriptList()
{
	return interactedScriptList;
}

void AActorBase::AddInteractedScript(FScriptItemData scriptItemData)
{
	interactedScriptList.Add(scriptItemData);
}

void AActorBase::RemoveInteractedScript(FScriptItemData scriptItemData)
{
	interactedScriptList.Remove(scriptItemData);
}

void AActorBase::UseSkillByKey(FKey key)
{
	UKeySkillMapData* keySkillMapData = UMainGameManager::GetInstance()->GetUserData()->GetKeySkillMapByActor(actorInfo->GetActorId());
	if (keySkillMapData != nullptr)
	{
		int skillId = keySkillMapData->GetSkillIdByKey(key);
		if (actorInfo->GetSkillMap().Contains(skillId))
		{
			USkillBase* skill = actorInfo->GetSkillMap()[skillId];
			skill->Use();
		}
	}
}

//void AActorBase::AttackPress()
//{
//	isAttackKeyDown = true;
//	if (isInAttack)
//	{
//	}
//	else
//	{
//		isInAttack = true;
//		attackComboIndex = 0;
//	}
//}
//
//void AActorBase::AttackRelease()
//{
//	isAttackKeyDown = false;
//}
//
//void AActorBase::ResetAttackCombo()
//{
//	isInAttack = false;
//	attackComboIndex = -1;
//}
//
//void AActorBase::SetAttackComboIndex(int newAttackComboIndex)
//{
//	attackComboIndex = newAttackComboIndex;
//}
//
//int AActorBase::GetAttackComboIndex()
//{
//	return attackComboIndex;
//}

void AActorBase::AddControlByAI()
{
	behaviorTree = LoadObject<UBehaviorTree>(NULL, TEXT("BehaviorTree'/Game/GameContent/AI/Main/MainBehaviorTree.MainBehaviorTree'"));
	
	if(mainAIController == nullptr)
	{
		mainAIController = GetWorld()->SpawnActor<AMainAIController>(GetActorInfo()->GetDefaultPosition(), GetActorInfo()->GetDefaultRotation());
	}
	Controller = mainAIController;
	mainAIController->Possess(this);
	mainAIController->SetTagetActor(ADirectorActor::GetInstance()->GetCurrentControlActor());
}

void AActorBase::RemoveControlByAI()
{
	if (Controller != nullptr)
	{
		Controller->UnPossess();
		Controller = nullptr;
		mainAIController->Destroy();
		mainAIController = nullptr;
	}
}

UBehaviorTree* AActorBase::GetBehaviorTree()
{
	return behaviorTree;
}

void AActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((executeNearbyAction || !nearbyActionIsCompleted))
	{
		if (actorInfo->GetNearbyParagraph() != nullptr)
		{
			if (!actorInfo->GetNearbyParagraph()->GetIsCompleted())
			{
				actorInfo->GetNearbyParagraph()->Update();
			}
			else
			{

				executeNearbyAction = false;
				nearbyActionIsCompleted = true;
			}
		}
	}
}

void AActorBase::SetActorInfo(UActorInfoBase* newActorInfo)
{
	if (newActorInfo == nullptr)
	{
		LogError(TEXT("设置actorinfo为空。"));
		return;
	}
	actorInfo = newActorInfo;

	
}

UActorInfoBase* AActorBase::GetActorInfo()
{
	return actorInfo;
}

void AActorBase::LoadModel()
{
	if (actorInfo == nullptr)
	{
		LogError(TEXT("当前演员信息为空不能加载模型。"));
		return;
	}
	FString modelPath = actorInfo->GetModelRootPath();
	FString modelName = actorInfo->GetModelName();
	if (!modelPath.IsEmpty())
	{
		//模型
		FString realModelPath = TEXT("SkeletalMesh'/Game/");
		realModelPath += modelPath + TEXT("/")+ modelName+ TEXT(".") + modelName + TEXT("'");
		USkeletalMesh* newMesh = LoadObject<USkeletalMesh>(NULL, realModelPath.GetCharArray().GetData());
		if (newMesh==nullptr)
		{
			LogError(FString::Printf(TEXT("演员信息Id:%d模型加载失败，路径：%s"), actorInfo->GetActorId(), *realModelPath));
		}
		else
		{
			GetMesh()->SetSkeletalMesh(newMesh);
		}
		//动画蓝图
		FString realAnimationPath = TEXT("/Game/");
		realAnimationPath += modelPath + TEXT("/") + modelName + TEXT("AnimBP.") + modelName + TEXT("AnimBP_C");
		UAnimBlueprintGeneratedClass* meshAnim = LoadObject<UAnimBlueprintGeneratedClass>(NULL, realAnimationPath.GetCharArray().GetData());
		if (meshAnim==nullptr)
		{
			LogError(FString::Printf(TEXT("演员信息Id:%d动画蓝图加载失败，路径：%s"), actorInfo->GetActorId(), *realAnimationPath));
		}
		else
		{
			GetMesh()->SetAnimInstanceClass(meshAnim);
		}
	}
	else
	{
		LogError(FString::Printf(TEXT("演员信息Id:%d模型路径为空"), actorInfo->GetActorId()));
	}
}

void AActorBase::ActorBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!nearbyActionIsCompleted || (UScriptManager::GetInstance() != nullptr && UScriptManager::GetInstance()->IsExecutingScript()))
	{
		return;
	}
	if (OtherActor == ADirectorActor::GetInstance())
	{
		if (actorInfo->GetNearbyParagraph()!=nullptr)
		{
			executeNearbyAction = true;
			nearbyActionIsCompleted = false;
			actorInfo->GetNearbyParagraph()->Start();
		}
	}
}

void AActorBase::ActorEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == ADirectorActor::GetInstance())
	{
		if (actorInfo->GetNearbyParagraph() != nullptr)
		{
			executeNearbyAction = false;
			currentActionIndex = 0;
		}
	}
}

bool AActorBase::IsInTalking()
{
	return isInTalking;
}

//bool AActorBase::IsInAttack()
//{
//	return isInAttack;
//}
//
//bool AActorBase::IsAttackKeyDown()
//{
//	return isAttackKeyDown;
//}

void AActorBase::StartTalk()
{
	isInTalking = true;
}

void AActorBase::StopTalk()
{
	isInTalking = false;
}

void AActorBase::StartPlayVoiceSound(USoundCue* soundBase)
{
	if (soundBase == nullptr)
	{
		LogError(TEXT("Actor在设置声音时传入值为空。"));
		return;
	}
	audioComponent->SetSound(soundBase);
	audioComponent->SoundClassOverride = UAudioManager::GetInstance()->GetVoiceSoundClass();
	audioComponent->Play();
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
