#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "RemoveActorAction.generated.h"

UCLASS()
class LEAVETHEPAST_API URemoveActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	URemoveActorAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	int actorInfoId = 0;
};
