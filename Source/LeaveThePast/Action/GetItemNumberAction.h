#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "GetItemNumberAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UGetItemNumberAction : public UActionBase
{
	GENERATED_BODY()
public:
	UGetItemNumberAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	int itemId = 0;
};
