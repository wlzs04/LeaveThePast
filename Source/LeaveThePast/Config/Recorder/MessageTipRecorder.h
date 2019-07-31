#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "MessageTipRecorder.generated.h"

//提示
UCLASS()
class LEAVETHEPAST_API UMessageTipRecorder : public URecorderBase
{
	GENERATED_BODY()
public:
	void LoadRecorder(FXmlNode* xmlNode) override;

	FString GetRecordName() override;

	//获得值
	UFUNCTION(BlueprintCallable)
	FString GetValue();

private:
	FString value;
};
