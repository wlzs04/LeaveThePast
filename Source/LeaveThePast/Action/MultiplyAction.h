#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "MultiplyAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UMultiplyAction : public UActionBase
{
	GENERATED_BODY()
public:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	TArray<UActionBase*> actionList; 
	int currentActionIndex = 0;
	bool isStart = false;//是否开始
};
