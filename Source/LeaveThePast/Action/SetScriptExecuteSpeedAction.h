#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetScriptExecuteSpeedAction.generated.h"

//指令：设置剧本执行速度
UCLASS()
class LEAVETHEPAST_API USetScriptExecuteSpeedAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	float scriptExecuteSpeed = 1;
};
