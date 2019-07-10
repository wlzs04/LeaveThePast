#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundMix.h"
#include "MainSoundMix.generated.h"

UCLASS()
class LEAVETHEPAST_API UMainSoundMix : public USoundMix
{
	GENERATED_BODY()

protected:
	//~ Begin UObject Interface.
	virtual FString GetDesc(void) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR
	virtual void BeginDestroy() override;
};
