#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetParagraphStateAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetParagraphStateAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetParagraphStateAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapter;
	int sectionId = 0;
	int paragraphId = 0;
	int state = 0;
	bool isCurrent = true;
};
