#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetShopUIStateAction.generated.h"

//指令：设置商店界面的状态
UCLASS()
class LEAVETHEPAST_API USetShopUIStateAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	bool isShow = true;
	FString shopConfigName;
};
