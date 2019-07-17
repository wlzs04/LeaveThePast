#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ActorBase.h"
#include "Sound/SoundCue.h"
#include "DirectorActor.generated.h"

UCLASS()
class LEAVETHEPAST_API ADirectorActor : public APawn
{
	GENERATED_BODY()

public:
	ADirectorActor();

	void InitActorList();

	//通过id设置当前摄像演员
	UFUNCTION(BlueprintCallable)
	void SetCameraActorById(int actorId);

	//通过当前摄像演员
	UFUNCTION(BlueprintCallable)
	AActorBase* GetCameraActor();

	void StartPlayBGMSound(USoundCue* soundBase);

	//设置目的地位置
	UFUNCTION(BlueprintCallable)
	void SetDestination(FVector newDestinationPosition);
	//获得目的地位置
	UFUNCTION(BlueprintCallable)
	FVector GetDestination();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveForwardInputFunction(float value);
	void MoveRightInputFunction(float value);
	void TurnInputFunction(float value);
	void LookUpInputFunction(float value);

	void ChangeControlActorInputFunction();
	void SystemInputFunction();
	void StartAccelerateInputFunction();
	void StopAccelerateInputFunction();
	void InteractedInputFunction();
	void DebugInputFunction();
	void MapInputFunction();
	void PauseInputFunction();
	
	UPROPERTY()
	UAudioComponent* audioComponent = nullptr;

	TArray<AActorBase*> canControlActorList;
	AActorBase* currentControlActor = nullptr;
	int currentControlActorIndex = 0;

	FVector destinationPosition = FVector(0, 0, 0);

	bool inMenuUI = false;
	bool inDebugUI = false;
	bool inMapUI = false;
	bool inPauseUI = false;
};
