#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "GetItemNumberAction.generated.h"

//指令：获得指定物品的数量
UCLASS()
class LEAVETHEPAST_API UGetItemNumberAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	int itemId = 0;
};
