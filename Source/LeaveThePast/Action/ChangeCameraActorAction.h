#pragma once

#include "CoreMinimal.h"
#include "ActionBase.h"
#include "ChangeCameraActorAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UChangeCameraActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	UChangeCameraActorAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	int actorInfoId = 0;
};
