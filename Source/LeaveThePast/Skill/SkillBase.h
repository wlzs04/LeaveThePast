#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Config/ActorSkillData.h"
#include "SkillBase.generated.h"

class FXmlNode;
class USkillRecorder;

UCLASS(BlueprintType)
class LEAVETHEPAST_API USkillBase : public UObject
{
	GENERATED_BODY()
public:
	void Load(FXmlNode* xmlNode);
	void Load(FSkillData* skillData);

	//使用技能
	void Use();

	UFUNCTION(BlueprintCallable)
	int GetSkillId();
	UFUNCTION(BlueprintCallable)
	int GetProficiency();
	UFUNCTION(BlueprintCallable)
	void SetKey(FKey newKey);
	UFUNCTION(BlueprintCallable)
	FKey GetKey();
	UFUNCTION(BlueprintCallable)
	FString GetKeyString();

	UFUNCTION(BlueprintCallable)
	USkillRecorder* GetSkillRecorder();
private:
	int skillId = 0;//技能Id
	int proficiency = 0;//熟练度
	FKey key;//快捷键

	USkillRecorder* skillRecorder = nullptr;
};
