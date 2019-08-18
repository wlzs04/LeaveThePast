#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "SkillRecorder.generated.h"

//技能类型
UENUM(BlueprintType)
enum class SkillEnum :uint8
{
	Unknown UMETA(DisplayName = "未知"),
	Attack UMETA(DisplayName = "攻击"),
	Defend UMETA(DisplayName = "防御"),
	Treat UMETA(DisplayName = "恢复"),
	Assist UMETA(DisplayName = "辅助"),
};

//技能
UCLASS()
class LEAVETHEPAST_API USkillRecorder : public URecorderBase
{
	GENERATED_BODY()
public:
	void LoadRecorder(FXmlNode* xmlNode) override;

	//获得名称
	UFUNCTION(BlueprintCallable)
	FString GetSkillName();

	//获得描述
	UFUNCTION(BlueprintCallable)
	FString GetDescription();

	//获得类型
	UFUNCTION(BlueprintCallable)
	SkillEnum GetSkillEnum();

	//获得图标路径
	UFUNCTION(BlueprintCallable)
	FString GetIconPath();
private:
	FString skillName;
	FString description;
	SkillEnum skillEnum = SkillEnum::Unknown;
	FString iconPath;
};
