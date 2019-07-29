#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetChapterStateAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetChapterStateAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetChapterStateAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapter;
	int state = 0;
	bool isCurrent = true;
};
