#include "ActorBase.h"
#include "..\..\Public\Action\ActionBase.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AActorBase::AActorBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorBase::BeginPlay()
{
	Super::BeginPlay();
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
	LoadModel();
}

void AActorBase::SetActorInfo(UActorInfoBase* newActorInfo)
{
	actorInfo = newActorInfo;
}

void AActorBase::LoadModel()
{
	FString modelPath = actorInfo->GetModelPath();
	if (!modelPath.IsEmpty())
	{
		FString modelName = TEXT("SkeletalMesh'/Game/");
		modelName += modelPath;
		modelName += TEXT("'");
		USkeletalMesh* newMesh = LoadObject<USkeletalMesh>(NULL, modelName.GetCharArray().GetData());
		if (newMesh==nullptr)
		{
			UE_LOG(LogLoad, Log, TEXT("演员Id:%d模型加载失败，路径：%s"), actorInfo->GetActorId(), *modelName);
		}
		else
		{
			GetMesh()->SetSkeletalMesh(newMesh);
		}
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
	return actorInfo->IsInTalking();
}

void AActorBase::StartTalk()
{
	actorInfo->StartTalk();
}

void AActorBase::StopTalk()
{
	actorInfo->StopTalk();
}
