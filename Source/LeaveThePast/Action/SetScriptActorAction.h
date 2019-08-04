#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/ScriptItemData.h"
#include "SetScriptActorAction.generated.h"

//指令：设置一个交互开启指定剧情事件到指定演员身上
UCLASS()
class LEAVETHEPAST_API USetScriptActorAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:

	int actorInfoId = 0;
	FScriptItemData scriptItemData;
	bool isNext = true;//是否将开启脚本设定为顺序下一个
};
