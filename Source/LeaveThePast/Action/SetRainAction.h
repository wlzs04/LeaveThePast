#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetRainAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetRainAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetRainAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	int rainFallValue = 0;
};
