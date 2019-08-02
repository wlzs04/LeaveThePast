#pragma once

#include "CoreMinimal.h"
#include "Action/MultiplyAction.h"
#include "RandomAction.generated.h"

//指令：如果随机到此项，则执行此项下的一系列指令，仅在随机(Random)指令节点下存在
UCLASS()
class LEAVETHEPAST_API URandomItemAction : public UMultiplyAction
{
	GENERATED_BODY()
public:
	virtual void Load(FXmlNode* xmlNode) override;

	UFUNCTION(BlueprintCallable)
	float GetProbability();

private:
	float probability = 1;//执行此指令的概率
};

//指令：随机执行列表中一项
UCLASS()
class LEAVETHEPAST_API URandomAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

	UFUNCTION(BlueprintCallable)
	TArray<URandomItemAction*> GetRandomItemList();

	bool SkipAction() override;
private:
	UPROPERTY()
	TArray<URandomItemAction*> randomItemList;
	int selectItemIndex = -1;
};
