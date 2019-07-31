#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScriptItemData.generated.h"

class FXmlNode;

//一条剧情数据，指向具体章节段
USTRUCT(BlueprintType)
struct FScriptItemData
{
	GENERATED_USTRUCT_BODY()

	FScriptItemData();

	FScriptItemData(FString newChapter, int newSectionId, int newParagraphId);

	bool operator == (const FScriptItemData& anotherData);

	void LoadFromXmlNode(FXmlNode* xmlNode);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString chapter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int sectionId = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int paragraphId = 0;
};