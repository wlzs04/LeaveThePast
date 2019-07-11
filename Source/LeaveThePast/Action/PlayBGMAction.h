#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "PlayBGMAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UPlayBGMAction : public UActionBase
{
	GENERATED_BODY()
public:
	UPlayBGMAction();
protected:
	//加载内容
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	int audioId = 9;

	float currentTime = 0;
	float startTime = 0;
};
