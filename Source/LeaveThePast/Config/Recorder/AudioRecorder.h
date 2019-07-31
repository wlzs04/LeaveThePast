#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "AudioRecorder.generated.h"

//音乐
UCLASS()
class LEAVETHEPAST_API UAudioRecorder : public URecorderBase
{
	GENERATED_BODY()
public:
	void LoadRecorder(FXmlNode* xmlNode) override;

	UFUNCTION(BlueprintCallable)
	FString GetAudioName();

	UFUNCTION(BlueprintCallable)
	int GetAudioType();

	UFUNCTION(BlueprintCallable)
	FString GetAudioRootPath();
private:
	FString audioName;
	int audioType = 0;//0 BGM 1 Voice 2 Effect
	FString audioRootPath;
};
