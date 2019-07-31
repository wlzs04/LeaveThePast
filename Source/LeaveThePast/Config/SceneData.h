#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScriptItemData.h"
#include "SceneData.generated.h"

class FXmlNode;

//场景中演员数据，一般用于保存读取场景中的演员信息
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

//场景中体积数据，一般用于保存读取场景中的体积信息
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