#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetCanControlAction.generated.h"

//指令：设置玩家是否可以控制演员
UCLASS()
class LEAVETHEPAST_API USetCanControlAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	bool canControl = true;
};
