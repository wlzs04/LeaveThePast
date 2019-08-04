#pragma once

#include "CoreMinimal.h"
#include "Config/RecorderBase.h"
#include "ItemRecorder.generated.h"

//物品
UCLASS()
class LEAVETHEPAST_API UItemRecorder : public URecorderBase
{
	GENERATED_BODY()
public:
	void LoadRecorder(FXmlNode* xmlNode) override;

	//获得名称
	UFUNCTION(BlueprintCallable)
	FString GetItemName();

	//获得描述
	UFUNCTION(BlueprintCallable)
	FString GetDescription();

	//获得图片路径
	UFUNCTION(BlueprintCallable)
	FString GetImagePath();

	//获得物品使用后执行的指令
	UFUNCTION(BlueprintCallable)
	FString GetUseItemExecuteActionString();

	//获得物品的价值(一般用于计算角色有多少钱，所以银票、铜钱、银两需要此值)
	UFUNCTION(BlueprintCallable)
	int GetItemWorth();
private:
	FString itemName;
	FString description;
	FString imagePath;
	FString useItemExecuteActionString;
	int itemWorth = 0;
};
