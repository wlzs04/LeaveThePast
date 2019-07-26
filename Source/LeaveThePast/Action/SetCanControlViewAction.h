#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetCanControlViewAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetCanControlViewAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetCanControlViewAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	bool canControlView = true;
};
