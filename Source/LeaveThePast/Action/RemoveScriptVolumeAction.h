#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/ScriptItemData.h"
#include "RemoveScriptVolumeAction.generated.h"

//指令：移除场景中符合条件的脚本体积
UCLASS()
class LEAVETHEPAST_API URemoveScriptVolumeAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:

	bool isCurrent = true;//是否移除当前脚本
	FScriptItemData scriptItemData;
};
