#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Section.generated.h"

class UParagraph;
class FXmlNode;

//节
UCLASS()
class LEAVETHEPAST_API USection : public UObject
{
	GENERATED_BODY()
public:
	void Update();
	void Load(FXmlNode* xmlNode);
	//bool GetIsCompleted();
	int GetSectionId();
	TArray<UParagraph*> GetParagraphList();
	//UParagraph* GetCurrentParagraph();
	//bool Start(int paragrapgId);
private:
	TArray<UParagraph*> paragraphList;
	//bool isCompleted = false;//是否完成
	//UParagraph* currentParagraph = nullptr;

	FString sectionName = TEXT("未命名");
	FString description = TEXT("无");
	int sectionId = 0;
};
