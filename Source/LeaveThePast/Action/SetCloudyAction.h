#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetCloudyAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetCloudyAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetCloudyAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	float cloudyValue = 0;
	
};
