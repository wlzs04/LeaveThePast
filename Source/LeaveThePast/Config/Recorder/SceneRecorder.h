#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "SceneRecorder.generated.h"

//场景
UCLASS()
class LEAVETHEPAST_API USceneRecorder : public URecorderBase
{
	GENERATED_BODY()
public:
	void LoadRecorder(FXmlNode* xmlNode) override;

	FString GetRecordName() override;

	UFUNCTION(BlueprintCallable)
	FString GetSceneName();

	UFUNCTION(BlueprintCallable)
	int GetBGMId();

	UFUNCTION(BlueprintCallable)
	TArray<int> GetSceneActorIdList();
private:
	FString sceneName;
	int bgmId = 0;

	TArray<int> sceneActorIdList;
};
