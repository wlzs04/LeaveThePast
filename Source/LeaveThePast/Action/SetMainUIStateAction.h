#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetMainUIStateAction.generated.h"

//指令：设置主界面的状态
UCLASS()
class LEAVETHEPAST_API USetMainUIStateAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	bool isShow = true;
};
