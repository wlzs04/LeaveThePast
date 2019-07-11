#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "RecorderBase.generated.h"

UCLASS()
class LEAVETHEPAST_API URecorderBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void LoadRecorder(FXmlNode* xmlNode);

	virtual FString GetRecordName();

	//获得Id
	UFUNCTION(BlueprintCallable)
		int GetId();

	//获得指定名称的值
	UFUNCTION(BlueprintCallable)
		FString GetValueByName(FString name);
protected:

	int id;
	TMap<FString, FString> valueMap;
};