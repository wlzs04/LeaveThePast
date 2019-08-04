#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/TimeData.h"
#include "SetTimeAction.generated.h"

//指令：设置当前时间
UCLASS()
class LEAVETHEPAST_API USetTimeAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FTimeData timeData;
};
