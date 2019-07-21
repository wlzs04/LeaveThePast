#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "RemoveCanControlActorAction.generated.h"

UCLASS()
class LEAVETHEPAST_API URemoveCanControlActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	URemoveCanControlActorAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;
private:
	int actorInfoId = 0;
};
