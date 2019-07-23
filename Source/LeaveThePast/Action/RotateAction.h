#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "RotateAction.generated.h"

UCLASS()
class LEAVETHEPAST_API URotateAction : public UActionBase
{
	GENERATED_BODY()
public:
	URotateAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	float actionTime = 1;
	//转身角度，默认Z方向，人正常转身的方向
	float value = 90;

	float currentTime = 0;
	float lastTime = 0;
	float startTime = 0;
};
