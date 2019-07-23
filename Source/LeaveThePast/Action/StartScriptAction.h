#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "StartScriptAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UStartScriptAction : public UActionBase
{
	GENERATED_BODY()
public:
	UStartScriptAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapterName;
	int sectionId = 0;
	int paragraphId = 0;
};
