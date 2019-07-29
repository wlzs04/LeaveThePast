#include "VolumeBase.h"
#include "../Manager/LogManager.h"

AVolumeBase::AVolumeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	interactedComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interacted"));
	interactedComponent->SetupAttachment(RootComponent);
	interactedComponent->OnComponentBeginOverlap.AddDynamic(this, &AVolumeBase::VolumeBeginOverlapEvent);
}

FString AVolumeBase::GetVolumeName()
{
	return volumeName;
}

bool AVolumeBase::GetCanSave()
{
	return canSave;
}

void AVolumeBase::LoadFromString(FString volumeValueString)
{
	LogError(FString::Printf(TEXT("%s体积未实现方法LoadFromString。"), *volumeName));
}

FString AVolumeBase::GetVolumeValue()
{
	LogError(FString::Printf(TEXT("%s体积未实现方法GetVolumeValue。"), *volumeName));
	return FString();
}

void AVolumeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AVolumeBase::VolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	VolumeBeginOverlapEventReal(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
