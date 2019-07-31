#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "StopScriptAction.generated.h"

//指令：停止当前执行的剧本
UCLASS()
class LEAVETHEPAST_API UStopScriptAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
};
