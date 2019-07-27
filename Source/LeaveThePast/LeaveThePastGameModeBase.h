#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LeaveThePastGameModeBase.generated.h"

class UMainGameManager;
class ADirectorActor;

UENUM(BlueprintType)
enum class MainGameStateEnum :uint8
{
	Init UMETA(DisplayName = "初始化"),
	Normal UMETA(DisplayName = "正常"),
};

UCLASS()
class LEAVETHEPAST_API ALeaveThePastGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	static ALeaveThePastGameModeBase* GetInstance();

	virtual void StartPlay() override;

	virtual void Tick(float deltaSeconds) override;
	
	//指游戏初始化后选择存档进入游戏
	//游戏开始
	UFUNCTION(BlueprintCallable)
	void InitFinish();

	//指游戏初始化后选择存档进入游戏
	//游戏开始
	UFUNCTION(BlueprintCallable)
	void StartGame();
	//游戏暂停
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	//游戏继续
	UFUNCTION(BlueprintCallable)
	void ContinueGame();
	//游戏结束
	UFUNCTION(BlueprintCallable)
	void EndGame();

	UFUNCTION(BlueprintCallable)
	UMainGameManager* GetGameManager();

	//获得天空球
	UFUNCTION(BlueprintCallable)
	AActor* GetSkyBPActor();

	//刷新天空
	UFUNCTION(BlueprintCallable)
	void RefreshSky();

	//获得剧本体积类
	//UFUNCTION(BlueprintCallable)
	//UClass* GetScriptVolumeBPClass();

	UFUNCTION(BlueprintImplementableEvent)
	void InitDebugCommand();
private:

	static ALeaveThePastGameModeBase* leaveThePastGameModeBase;

	UPROPERTY()
	UMainGameManager* gameManager = nullptr;

	UPROPERTY()
	ADirectorActor* directorActor = nullptr;

	MainGameStateEnum  mainGameState = MainGameStateEnum::Init;

	//剧本体积类
	//UPROPERTY()
	//UClass* scriptVolumeBPClass = nullptr;

	//天空球
	UPROPERTY()
	AActor* skyBPActor = nullptr;
};
