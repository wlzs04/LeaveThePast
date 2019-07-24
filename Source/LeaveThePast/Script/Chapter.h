#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Section.h"
#include "Chapter.generated.h"

UCLASS(BlueprintType)
class LEAVETHEPAST_API UChapter : public UObject
{
	GENERATED_BODY()
public:
	void Update();
	void Load(FString newChapterPath);
	bool GetIsCompleted();
	USection* GetCurrentSection();
	void Start(int sectionId, int paragrapgId);

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
	bool isCompleted = false;//是否完成
	USection* currentSection = nullptr;

	FString chapterPath = TEXT("");
	FString chapterIndexName = TEXT("未命名");
	FString chapterName = TEXT("未命名");
	FString description = TEXT("无");
};
