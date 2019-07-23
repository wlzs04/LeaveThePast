#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "PlayBGMAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UPlayBGMAction : public UActionBase
{
	GENERATED_BODY()
public:
	UPlayBGMAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	int audioId = 9;
};
