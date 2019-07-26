#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetCanControlMoveAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetCanControlMoveAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetCanControlMoveAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	bool canControlMove = true;
};
