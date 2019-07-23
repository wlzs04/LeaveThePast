#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "Action/MultiplyAction.h"
#include "ConditionAction.generated.h"

UENUM(BlueprintType)
enum class ConditionType :uint8
{
	Equal UMETA(DisplayName = "相等"),
	More UMETA(DisplayName = "大于"),
	Less UMETA(DisplayName = "小于"),
};

UCLASS()
class LEAVETHEPAST_API UConditionItemAction : public UMultiplyAction
{
	GENERATED_BODY()
public:
	UConditionItemAction();
	virtual void Load(FXmlNode* xmlNode) override;
	bool CheckCondition(FString checkConditionValue);
private:
	ConditionType conditionType = ConditionType::Equal;
	bool isDefault = false;
	FString conditionValue;
};

UCLASS()
class LEAVETHEPAST_API UConditionAction : public UActionBase
{
	GENERATED_BODY()
public:
	UConditionAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;
private:
	TArray<UConditionItemAction*> conditionItemList;
	FString actionString;

	UConditionItemAction* selectConditionItemAction = nullptr;
};
