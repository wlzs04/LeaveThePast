#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "../Config/UserData.h"
#include "AddScriptVolumeAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UAddScriptVolumeAction : public UActionBase
{
	GENERATED_BODY()
public:
	UAddScriptVolumeAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:

	FVector position;
	FScriptRecorderInfo scriptRecorderIndfo;
	bool isNext = true;//是否将开启脚本设定为顺序下一个
};
