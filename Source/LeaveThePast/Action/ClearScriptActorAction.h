#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/UserData.h"
#include "ClearScriptActorAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UClearScriptActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	UClearScriptActorAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:

	int actorInfoId = 0;
	bool isCurrent = true;//是否让演员移除当前脚本
	FScriptRecorderInfo scriptRecorderIndfo;
};