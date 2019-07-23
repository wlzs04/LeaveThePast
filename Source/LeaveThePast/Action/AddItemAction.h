#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "AddItemAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UAddItemAction : public UActionBase
{
	GENERATED_BODY()
public:
	UAddItemAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	int itemId = 0;
	int itemNumber = 1;
};
