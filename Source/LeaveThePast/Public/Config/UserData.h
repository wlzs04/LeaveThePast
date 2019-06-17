#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserData.generated.h"

class UGameManager;

UCLASS()
class LEAVETHEPAST_API UUserData : public UObject
{
	GENERATED_BODY()
public:
	UUserData();

	void Load();

	void Save();

	//获得物品map
	UFUNCTION(BlueprintCallable)
	TMap<int, int> GetItemMap();

protected:
	//保存路径
	FString savePath;

	TMap<int, int> itemMap;
};
