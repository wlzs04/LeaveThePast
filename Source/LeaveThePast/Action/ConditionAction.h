#pragma once

#include "CoreMinimal.h"
#include "Action/MultiplyAction.h"
#include "ConditionAction.generated.h"

UENUM(BlueprintType)
enum class ConditionType :uint8
{
	Unknown UMETA(DisplayName = "未知"),
	Equal UMETA(DisplayName = "相等"),
	More UMETA(DisplayName = "大于"),
	Less UMETA(DisplayName = "小于"),
};

//指令：如果条件符合,则执行此选项下的一系列指令，仅在条件(Condition)指令节点下存在
UCLASS()
class LEAVETHEPAST_API UConditionItemAction : public UMultiplyAction
{
	GENERATED_BODY()
public:
	virtual void Load(FXmlNode* xmlNode) override;
	bool CheckCondition(FString checkConditionValue);
private:
	ConditionType conditionType = ConditionType::Unknown;
	bool isDefault = false;
	FString conditionValue;
};

//指令：根据条件执行指令
UCLASS()
class LEAVETHEPAST_API UConditionAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
	bool SkipAction() override;
private:
	UPROPERTY()
	TArray<UConditionItemAction*> conditionItemList;
	FString actionString;
	UPROPERTY()
	UConditionItemAction* selectConditionItemAction = nullptr;
};
