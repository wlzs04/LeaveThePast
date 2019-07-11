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
	static UUIManager* GetInstance();

	void Init();

	//加载指定界面
	UFUNCTION(BlueprintCallable)
	UUserWidget* LoadUIByName(FString uiName);

	//弹提示
	UFUNCTION(BlueprintCallable)
	void AddMessageTip(FString value);

	//弹提示
	UFUNCTION(BlueprintCallable)
	void AddMessageTipById(int id);

	//显示谈话界面
	UFUNCTION(BlueprintCallable)
	void ShowTalkUI(FString talkValue, FString actorName, float continueTime, FString headImagePath, bool isLeft = true);

	//显示主界面
	UFUNCTION(BlueprintCallable)
	void ShowMainUI();

	//隐藏主界面
	UFUNCTION(BlueprintCallable)
	void HideMainUI();

	//显示菜单界面
	UFUNCTION(BlueprintCallable)
	void ShowMenuUI();

	//隐藏菜单界面
	UFUNCTION(BlueprintCallable)
	void HideMenuUI();

	//显示商品界面
	UFUNCTION(BlueprintCallable)
	void ShowShopUI();

	//隐藏商品界面
	UFUNCTION(BlueprintCallable)
	void HideShopUI();
private:
	//初始化常用UI
	void InitUI();

	static UUIManager* uiManager;

	UPROPERTY()
	UUserWidget* mainUIWidget = nullptr;

	UPROPERTY()
	UUserWidget* talkUIWidget = nullptr;

	UPROPERTY()
	UUserWidget* menuUIWidget = nullptr;

	UPROPERTY()
	UUserWidget* shopUIWidget = nullptr;
};
