#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Chapter.generated.h"

class USection;

//章
UCLASS(BlueprintType)
class LEAVETHEPAST_API UChapter : public UObject
{
	GENERATED_BODY()
public:
	void Load(FString newChapterPath);

	UFUNCTION(BlueprintCallable)
	TArray<USection*> GetSectionList();

	UFUNCTION(BlueprintCallable)
	FString GetChapterName();
	UFUNCTION(BlueprintCallable)
	void SetChapterIndexName(FString newChapterIndexName);
	UFUNCTION(BlueprintCallable)
	FString GetChapterIndexName();
	UFUNCTION(BlueprintCallable)
	FString GetChapterDescription();
private:
	TArray<USection*> sectionList;

	FString chapterPath = TEXT("");
	FString chapterIndexName = TEXT("未命名");
	FString chapterName = TEXT("未命名");
	FString description = TEXT("无");
};
