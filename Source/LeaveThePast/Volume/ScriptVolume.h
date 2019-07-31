#pragma once

#include "CoreMinimal.h"
#include "VolumeBase.h"
#include "../Config/ScriptItemData.h"
#include "ScriptVolume.generated.h"

//剧本体积，玩家进入体积会执行剧情
UCLASS()
class LEAVETHEPAST_API AScriptVolume : public AVolumeBase
{
	GENERATED_BODY()
public:
	AScriptVolume();

	virtual void LoadFromString(FString volumeValueString) override;

	virtual FString GetVolumeValue() override;

	void SetInfo(FScriptItemData newScriptItemData);
	FScriptItemData GetScriptItemData();
private:
	virtual void VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FScriptItemData scriptItemData;
};
