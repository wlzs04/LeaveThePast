#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "SetMainUIStateAction.generated.h"

UCLASS()
class LEAVETHEPAST_API USetMainUIStateAction : public UActionBase
{
	GENERATED_BODY()
public:
	USetMainUIStateAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

private:
	bool isShow = true;
};
