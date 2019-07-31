#pragma once

#include "CoreMinimal.h"
#include "Volume/VolumeBase.h"
#include "SceneVolume.generated.h"

//场景体积，玩家进入体积代表进入场景
UCLASS()
class LEAVETHEPAST_API ASceneVolume : public AVolumeBase
{
	GENERATED_BODY()
public:
private:
	virtual void VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int sceneId = 0;
};
