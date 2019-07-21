#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "RemoveMoneyAction.generated.h"

UCLASS()
class LEAVETHEPAST_API URemoveMoneyAction : public UActionBase
{
	GENERATED_BODY()
public:
	URemoveMoneyAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	int number = 0;
};
