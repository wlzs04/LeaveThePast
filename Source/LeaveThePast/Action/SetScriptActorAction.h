#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/UserData.h"
#include "SetScriptActorAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetScriptActorAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetScriptActorAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:

	int actorInfoId = 0;
	FScriptRecorderInfo scriptRecorderIndfo;
	bool isNext = true;//是否将开启脚本设定为顺序下一个
};
