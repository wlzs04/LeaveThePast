#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/ScriptItemData.h"
#include "RemoveScriptVolumeAction.generated.h"

UCLASS()
class LEAVETHEPAST_API URemoveScriptVolumeAction : public UActionBase
{
	GENERATED_BODY()
public:
	URemoveScriptVolumeAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:

	bool isCurrent = true;//是否移除当前脚本
	FScriptItemData scriptItemData;
};
