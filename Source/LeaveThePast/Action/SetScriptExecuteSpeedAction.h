#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetScriptExecuteSpeedAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetScriptExecuteSpeedAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetScriptExecuteSpeedAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	float scriptExecuteSpeed = 1;
};
