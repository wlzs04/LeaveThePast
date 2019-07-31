#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "RecorderBase.generated.h"

//记录基类，配置表中的一条数据
UCLASS(BlueprintType)
class LEAVETHEPAST_API URecorderBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void LoadRecorder(FXmlNode* xmlNode);

	//获得Id
	UFUNCTION(BlueprintCallable)
	int GetId();
protected:
	int id;
};
