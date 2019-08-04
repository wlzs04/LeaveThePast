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
	void Load(FXmlNode* xmlNode);

	UFUNCTION(BlueprintCallable)
	int GetSectionId();
	UFUNCTION(BlueprintCallable)
	FString GetSectionName();
	UFUNCTION(BlueprintCallable)
	FString GetSectionDescription();

	UFUNCTION(BlueprintCallable)
	TArray<UParagraph*> GetParagraphList();
private:
	TArray<UParagraph*> paragraphList;

	FString sectionName = TEXT("未命名");
	FString description = TEXT("无");
	int sectionId = 0;
};
