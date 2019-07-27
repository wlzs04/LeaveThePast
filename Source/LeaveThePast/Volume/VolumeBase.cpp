#include "VolumeBase.h"

AVolumeBase::AVolumeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	interactedComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interacted"));
	interactedComponent->SetupAttachment(RootComponent);
	interactedComponent->OnComponentBeginOverlap.AddDynamic(this, &AVolumeBase::VolumeBeginOverlapEvent);
}

void AVolumeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AVolumeBase::VolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	VolumeBeginOverlapEventReal(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
