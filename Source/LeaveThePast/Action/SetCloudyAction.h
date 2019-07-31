#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetCloudyAction.generated.h"

//指令：设置天空中云的程度
UCLASS()
class LEAVETHEPAST_API USetCloudyAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	float cloudyValue = 0;
	
};
