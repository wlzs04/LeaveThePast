#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetRainAction.generated.h"

//指令：设置天空中雨的程度
UCLASS()
class LEAVETHEPAST_API USetRainAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	int rainValue = 0;
};
