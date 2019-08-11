#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

class FXmlNode;

UCLASS()
class LEAVETHEPAST_API USkillBase : public UObject
{
	GENERATED_BODY()
public:
	void Load(FXmlNode* xmlNode);

	UFUNCTION(BlueprintCallable)
	int GetSkillId();
	UFUNCTION(BlueprintCallable)
	int GetProficiency();
private:
	int skillId = 0;//技能Id
	int proficiency = 0;//熟练度
};
