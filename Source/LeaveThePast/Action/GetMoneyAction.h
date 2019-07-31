#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "GetMoneyAction.generated.h"

//指令：获得钱的数量
UCLASS()
class LEAVETHEPAST_API UGetMoneyAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
};