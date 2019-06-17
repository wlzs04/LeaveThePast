#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SceneData.h"
#include "WorldData.generated.h"

UCLASS()
class LEAVETHEPAST_API UWorldData : public UObject
{
	GENERATED_BODY()
public:
	UWorldData();

	void Load();
private:
	//保存路径
	FString savePath;

	TArray<USceneData*> sceneDataList;
};
