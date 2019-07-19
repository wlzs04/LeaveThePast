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

	void LoadFromXmlNode(FXmlNode* xmlNode);

	void SetActorId(int newActorId)
	{
		actorId = newActorId;
	}

	void SetActorName(FString newActorName)
	{
		actorName = newActorName;
		needReplaceActorName = true;
	}

	void SetPosition(FVector newPosition)
	{
		position = newPosition;
		needReplacePosition = true;
	}

	void SetRotation(FRotator newRotation)
	{
		rotation = newRotation;
		needReplaceRotation = true;
	}

	int actorId;
	bool needReplaceActorName = false;
	FString actorName;
	bool needReplacePosition = false;
	FVector position;
	bool needReplaceRotation = false;
	FRotator rotation;
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
