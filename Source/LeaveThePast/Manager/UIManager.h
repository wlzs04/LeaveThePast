#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <UMG.h>
#include "UIManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class LEAVETHEPAST_API UUIManager : public UObject
{
	GENERATED_BODY()
public:
	UUIManager();
	static UUIManager* GetInstance();

	void Init();

	//弹提示
	UFUNCTION(BlueprintCallable)
	void AddMessageTip(FString value);

	//弹提示
	UFUNCTION(BlueprintCallable)
	void AddMessageTipById(int id);

	//显示谈话界面
	UFUNCTION(BlueprintCallable)
	void SetTalkUI(FString talkValue, FString actorName, float continueTime = 1, FString headImagePath = TEXT("GameContent/Resource/Others/Image/Unknown.jpg"), bool isLeft = true);

	//显示指定界面
	UUserWidget* ShowUIByName(FString uiName);

private:
	static UUIManager* uiManager;
};
