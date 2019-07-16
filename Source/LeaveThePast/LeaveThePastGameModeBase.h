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

	UFUNCTION(BlueprintCallable)
	UMainGameManager* GetGameManager();
private:

	UPROPERTY()
	UMainGameManager* gameManager = nullptr;

	UPROPERTY()
	ADirectorActor* directorActor = nullptr;
};
