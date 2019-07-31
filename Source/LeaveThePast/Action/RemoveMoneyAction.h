#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "RemoveMoneyAction.generated.h"

//指令：移除指定钱数，并不推荐使用此指令，请使用移除物品(RemoveItem)指令代替
UCLASS()
class LEAVETHEPAST_API URemoveMoneyAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	int number = 0;
};
