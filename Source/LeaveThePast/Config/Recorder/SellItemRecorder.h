#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "SellItemRecorder.generated.h"

//售货
UCLASS()
class LEAVETHEPAST_API USellItemRecorder : public URecorderBase
{
	GENERATED_BODY()
public:
	void LoadRecorder(FXmlNode* xmlNode) override;

	UFUNCTION(BlueprintCallable)
	int GetItemId();

	UFUNCTION(BlueprintCallable)
	int GetPrice();
private:
	int itemId = 0;
	int price = 0;
};
