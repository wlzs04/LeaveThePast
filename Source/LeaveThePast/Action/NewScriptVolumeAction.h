#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "NewScriptVolumeAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UNewScriptVolumeAction : public UActionBase
{
	GENERATED_BODY()
public:
	UNewScriptVolumeAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;
private:

	FVector position;
	bool isNext = true;//是否将开启脚本设定为顺序下一个
};
