#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <LeaveThePast\Public\Script\Paragraph.h>
#include "Section.generated.h"

UCLASS()
class LEAVETHEPAST_API USection : public UObject
{
	GENERATED_BODY()
public:
	void Update();
	void Load(FXmlNode* xmlNode);
	bool GetIsCompleted();
	UParagraph* GetCurrentParagraph();
	void Start();
private:
	TArray<UParagraph*> paragraphList;
	bool isCompleted = false;//是否完成
	UParagraph* currentParagraph = nullptr;

	FString sectionName = TEXT("未命名");
	FString description = TEXT("无");
};
