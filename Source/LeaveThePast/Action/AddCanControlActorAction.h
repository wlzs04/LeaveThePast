#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "AddCanControlActorAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UAddCanControlActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	UAddCanControlActorAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;
private:
	int actorInfoId = 0;
};
