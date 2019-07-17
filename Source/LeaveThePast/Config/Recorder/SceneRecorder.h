#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "SceneRecorder.generated.h"

USTRUCT(BlueprintType)
struct FSceneActorInfo
{
	GENERATED_USTRUCT_BODY()
	
	FSceneActorInfo()
	{
		actorId = 0;
	}

	void SetActorId(int newActorId)
	{
		actorId = newActorId;
	}

	void SetActorName(FString newActorName)
	{
		actorName = newActorName;
		needReplaceActorName = true;
	}

	void SetDefaultPosition(FVector newDefaultPosition)
	{
		defaultPosition = newDefaultPosition;
		needReplaceDefaultPosition = true;
	}

	void SetDefaultRotation(FRotator newDefaultRotation)
	{
		defaultRotation = newDefaultRotation;
		needReplaceDefaultRotation = true;
	}

	int actorId;
	bool needReplaceActorName = false;
	FString actorName;
	bool needReplaceDefaultPosition = false;
	FVector defaultPosition;
	bool needReplaceDefaultRotation = false;
	FRotator defaultRotation;
};

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
	TArray<FSceneActorInfo> GetSceneActorList();
private:
	FString sceneName;
	int bgmId = 0;

	TArray<FSceneActorInfo> sceneActorList;
};
