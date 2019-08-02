#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "MultiplyAction.generated.h"

//指令：拥有多个指令，一般用于被继承，不会直接使用
UCLASS()
class LEAVETHEPAST_API UMultiplyAction : public UActionBase
{
	GENERATED_BODY()
public:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
	bool SkipAction() override;
private:
	UPROPERTY()
	TArray<UActionBase*> actionList; 
	int currentActionIndex = 0;
};
