#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/TimeData.h"
#include "SetTimeAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetTimeAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetTimeAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	FTimeData timeData;
};
