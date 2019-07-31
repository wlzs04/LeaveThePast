#pragma once

#include "CoreMinimal.h"
#include "Action/MultiplyAction.h"
#include "OptionAction.generated.h"

//指令：如果选择此项，则执行此选项下的一系列指令，仅在选项(Option)指令节点下存在
UCLASS()
class LEAVETHEPAST_API UOptionItemAction : public UMultiplyAction
{
	GENERATED_BODY()
public:
	virtual void Load(FXmlNode* xmlNode) override;

	UFUNCTION(BlueprintCallable)
	FString GetOptionText();

private:
	FString optionText;
};

//指令：显示选项界面，由玩家进行选择
UCLASS()
class LEAVETHEPAST_API UOptionAction : public UActionBase
{
	GENERATED_BODY()
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual FString ExecuteReal() override;

	UFUNCTION(BlueprintCallable)
	TArray<UOptionItemAction*> GetOptionItemList();

	UFUNCTION(BlueprintCallable)
	void SetSelectItemIndex(int itemIndex);

	bool SkipAction() override;
private:
	TArray<UOptionItemAction*> optionItemList;
	int selectItemIndex = -1;
};
