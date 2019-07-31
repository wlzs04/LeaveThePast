#pragma once

#include "CoreMinimal.h"
#include "Volume/VolumeBase.h"
#include "ExecuteActionVolume.generated.h"

//场景体积，玩家进入体积会执行一段自定义的指令
UCLASS()
class LEAVETHEPAST_API AExecuteActionVolume : public AVolumeBase
{
	GENERATED_BODY()
private:
	virtual void VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString actionString;
};
