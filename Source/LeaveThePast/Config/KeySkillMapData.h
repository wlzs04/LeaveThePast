#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputCoreTypes.h"
#include "KeySkillMapData.generated.h"

class FXmlNode;

//按键和技能映射类
UCLASS()
class LEAVETHEPAST_API UKeySkillMapData : public UObject
{
	GENERATED_BODY()

public:
	void LoadFromXmlNode(FXmlNode* xmlNode);
	
	//通过key获得对应技能Id
	int GetSkillIdByKey(FKey key);
private:
	TMap<FKey, int> keySkillMap;
};
