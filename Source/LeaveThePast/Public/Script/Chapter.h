#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <LeaveThePast\Public\Script\Section.h>
#include "Chapter.generated.h"

UCLASS()
class LEAVETHEPAST_API UChapter : public UObject
{
	GENERATED_BODY()
public:
	void Update();
	void Load(FString newChapterPath);
	bool GetIsCompleted();
	USection* GetCurrentSection();
	void Start();
private:
	TArray<USection*> sectionList;
	bool isCompleted = false;//是否完成
	USection* currentSection = nullptr;

	FString chapterPath = TEXT("");
	FString chatperName = TEXT("未命名");
	FString description = TEXT("无");
};
