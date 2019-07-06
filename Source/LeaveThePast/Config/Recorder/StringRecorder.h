#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "StringRecorder.generated.h"

UCLASS()
class LEAVETHEPAST_API UStringRecorder : public URecorderBase
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
