#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "Action/MultiplyAction.h"
#include "OptionAction.generated.h"

UCLASS()
class LEAVETHEPAST_API UOptionItemAction : public UMultiplyAction
{
	GENERATED_BODY()
public:
	UOptionItemAction();
	virtual void Load(FXmlNode* xmlNode) override;

	UFUNCTION(BlueprintCallable)
	FString GetOptionText();

private:
	FString optionText;
};

UCLASS()
class LEAVETHEPAST_API UOptionAction : public UActionBase
{
	GENERATED_BODY()
public:
	UOptionAction();
protected:
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

	UFUNCTION(BlueprintCallable)
	TArray<UOptionItemAction*> GetOptionItemList();

	UFUNCTION(BlueprintCallable)
	void SetSelectItemIndex(int itemIndex);
private:
	TArray<UOptionItemAction*> optionItemList;
	int selectItemIndex = -1;
};
