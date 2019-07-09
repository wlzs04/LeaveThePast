#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "AudioRecorder.generated.h"

UCLASS()
class LEAVETHEPAST_API UAudioRecorder : public URecorderBase
{
	GENERATED_BODY()
public:
	void LoadRecorder(FXmlNode* xmlNode) override;

	FString GetRecordName() override;

	//获得值
	UFUNCTION(BlueprintCallable)
	FString GetAudioName();

	UFUNCTION(BlueprintCallable)
	FString GetAudioRootPath();
private:
	FString audioName;
	FString audioRootPath;
};
