#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "RemoveItemAction.generated.h"

//指令：移除指定物品
UCLASS()
class LEAVETHEPAST_API URemoveItemAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	int itemId = 0;
	int number = 1;
};
