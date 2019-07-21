#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <UMG.h>
#include "UIManager.generated.h"

class UOptionAction;

UCLASS(BlueprintType, Blueprintable)
class LEAVETHEPAST_API UUIManager : public UObject
{
	GENERATED_BODY()
public:
	static UUIManager* GetInstance();

	void Init();

	//加载指定界面
	UFUNCTION(BlueprintCallable)
	UUserWidget* LoadUIByName(FString uiName,FString foldName=TEXT(""));

	//显示初始界面
	UFUNCTION(BlueprintCallable)
	void ShowInitUI();

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
	void ShowShopUI(FString shopConfigName);

	//隐藏商品界面
	UFUNCTION(BlueprintCallable)
	void HideShopUI();

	//显示调试界面
	UFUNCTION(BlueprintCallable)
	void ShowDebugUI();

	//隐藏调试界面
	UFUNCTION(BlueprintCallable)
	void HideDebugUI();

	//显示调试界面
	UFUNCTION(BlueprintCallable)
	void ShowMapUI();

	//隐藏调试界面
	UFUNCTION(BlueprintCallable)
	void HideMapUI();

	//显示暂停界面
	UFUNCTION(BlueprintCallable)
	void ShowPauseUI();

	//隐藏暂停界面
	UFUNCTION(BlueprintCallable)
	void HidePauseUI();

	//显示选项界面
	UFUNCTION(BlueprintCallable)
	void ShowOptionUI(UOptionAction* optionAction);

	//隐藏选项界面
	UFUNCTION(BlueprintCallable)
	void HideOptionUI();
	
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

	UPROPERTY()
	UUserWidget* debugUIWidget = nullptr;

	UPROPERTY()
	UUserWidget* mapUIWidget = nullptr;

	UPROPERTY()
	UUserWidget* pauseUIWidget = nullptr;

	UPROPERTY()
	UUserWidget* optionUIWidget = nullptr;
};
