#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleManager.generated.h"

UCLASS()
class LEAVETHEPAST_API UBattleManager : public UObject
{
	GENERATED_BODY()
public:
	static UBattleManager* GetInstance();

	void Init();

	//开始战斗
	void StartBattle();
	//停止战斗
	void StopBattle();

	//是否在战斗中
	bool IsInBattle();
private:

	static UBattleManager* battleManager;

	bool inBattle = false;//是否在战斗中
};
