#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetSectionStateAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetSectionStateAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetSectionStateAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapter;
	int sectionId = 0;
	int state = 0;
	bool isCurrent = true;
};
