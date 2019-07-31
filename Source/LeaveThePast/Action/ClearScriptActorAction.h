#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/ScriptItemData.h"
#include "ClearScriptActorAction.generated.h"

//指令：清除演员挂载的脚本
UCLASS()
class LEAVETHEPAST_API UClearScriptActorAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:

	int actorInfoId = 0;
	bool isCurrent = true;//是否让演员移除当前脚本
	FScriptItemData scriptItemData;
};
