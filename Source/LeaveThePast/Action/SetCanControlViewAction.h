#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetCanControlViewAction.generated.h"

//指令：设置玩家是否可以控制视角
UCLASS()
class LEAVETHEPAST_API USetCanControlViewAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	bool canControlView = true;
};
