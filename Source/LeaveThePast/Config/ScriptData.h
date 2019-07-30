#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScriptData.generated.h"

UCLASS(BlueprintType)
class USectionData : public UObject
{
	GENERATED_BODY()
public:

	int sectionId = 0;
	int state = 0;//0 未开始 1 进行中 2 完成 3 失败
	TMap<int, int> paragraphMap;
};

UCLASS(BlueprintType)
class UChapterData : public UObject
{
	GENERATED_BODY()
public:

	FString chapterName;
	int state = 0;//0 未开始 1 进行中 2 完成 3 失败
    UPROPERTY()
	TMap<int, USectionData*> sectionMap;
};