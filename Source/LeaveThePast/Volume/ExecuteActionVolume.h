#pragma once

#include "CoreMinimal.h"
#include "Volume/VolumeBase.h"
#include "ExecuteActionVolume.generated.h"

UCLASS()
class LEAVETHEPAST_API AExecuteActionVolume : public AVolumeBase
{
	GENERATED_BODY()
private:
	virtual void VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString actionString;
};
