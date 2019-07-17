#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LeaveThePastGameModeBase.generated.h"

class UMainGameManager;
class ADirectorActor;

UCLASS()
class LEAVETHEPAST_API ALeaveThePastGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void StartPlay() override;

	virtual void Tick(float deltaSeconds) override;

	//指游戏初始化后选择存档进入游戏
	//游戏开始
	UFUNCTION(BlueprintCallable)
	void StartGame();
	//游戏暂停
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	//游戏暂停
	UFUNCTION(BlueprintCallable)
	void ContinueGame();
	//游戏结束
	UFUNCTION(BlueprintCallable)
	void EndGame();

	UFUNCTION(BlueprintCallable)
	UMainGameManager* GetGameManager();
private:

	UPROPERTY()
	UMainGameManager* gameManager = nullptr;

	UPROPERTY()
	ADirectorActor* directorActor = nullptr;
};
