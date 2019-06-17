#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "ItemRecorder.generated.h"

UCLASS()
class LEAVETHEPAST_API UItemRecorder : public URecorderBase
{
	GENERATED_BODY()
public:
	void LoadRecorder(FXmlNode* xmlNode) override;

	FString GetRecordName() override;

	//获得名称
	UFUNCTION(BlueprintCallable)
	FString GetItemName();

	//获得类型
	UFUNCTION(BlueprintCallable)
	int GetTtemType();

	//获得描述
	UFUNCTION(BlueprintCallable)
	FString GetDescript();
private:
	FString itemName;
	int itemType;
	FString descript;
	
};
