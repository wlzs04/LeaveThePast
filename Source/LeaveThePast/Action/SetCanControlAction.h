#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetCanControlAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetCanControlAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetCanControlAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	bool canControl = true;
};
