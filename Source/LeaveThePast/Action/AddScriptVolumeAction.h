#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/ScriptItemData.h"
#include "AddScriptVolumeAction.generated.h"

//指令：添加剧本体积，默认当前控制演员进入体积内触发
UCLASS()
class LEAVETHEPAST_API UAddScriptVolumeAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:

	FVector position;
	FScriptItemData scriptItemData;
	bool isNext = true;//是否将开启脚本设定为顺序下一个
};
