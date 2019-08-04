#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetSectionStateAction.generated.h"

//指令：设置剧情中指定节的状态，一般用于标记此节是否完成
UCLASS()
class LEAVETHEPAST_API USetSectionStateAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Load(TArray<FString> paramList) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	FString chapter;
	int sectionId = 0;
	int state = 0;
	bool isCurrent = true;
};
