#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "MoveAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UMoveAction : public UActionBase
{
	GENERATED_BODY()
public:
	UMoveAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	//移动方向
	FVector direction;
	float speed = 100;
	float actionTime = 1;

	float currentTime = 0;
	float startTime = 0;
};
