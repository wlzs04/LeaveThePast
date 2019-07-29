#pragma once

#include "CoreMinimal.h"
#include "VolumeBase.h"
#include "../Config/UserData.h"
#include "ScriptVolume.generated.h"

UCLASS()
class LEAVETHEPAST_API AScriptVolume : public AVolumeBase
{
	GENERATED_BODY()
public:
	AScriptVolume();

	virtual void LoadFromString(FString volumeValueString) override;

	virtual FString GetVolumeValue() override;

	void SetInfo(FScriptRecorderInfo newScriptRecorderIndfo);
	FScriptRecorderInfo GetScriptInfo();
private:
	virtual void VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FScriptRecorderInfo scriptRecorderInfo;
};
