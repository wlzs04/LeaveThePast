#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScriptItemData.h"
#include "SceneData.generated.h"

class FXmlNode;

UCLASS(BlueprintType)
class USceneActorData : public UObject
{
	GENERATED_BODY()
public:
	void LoadFromXmlNode(FXmlNode* xmlNode);

	int actorId = 0;
	FVector position;
	FRotator rotation;

	TArray<FScriptItemData> scriptItemDataList;
};

UCLASS(BlueprintType)
class USceneVolumeData : public UObject
{
	GENERATED_BODY()
public:
	void LoadFromXmlNode(FXmlNode* xmlNode);

	FString volumeType;
	FVector position;
	FString value;
};