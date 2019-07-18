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

	//初始化可控演员，从用户存档内读取
	void InitCanControlActor();

	//通过id设置当前控制演员
	UFUNCTION(BlueprintCallable)
	void SetControlActorById(int actorId);

	//设置当前控制演员
	UFUNCTION(BlueprintCallable)
	void SetControlActor(AActorBase* actor);

	//通过当前控制演员
	UFUNCTION(BlueprintCallable)
	AActorBase* GetControlActor();

	//通过可控演员列表
	UFUNCTION(BlueprintCallable)
	TArray<AActorBase*> GetCanControlActorList();

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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* interactedComponent = nullptr;

	TArray<AActorBase*> canControlActorList;
	AActorBase* currentControlActor = nullptr;
	int currentControlActorIndex = 0;

	FVector destinationPosition = FVector(0, 0, 0);

	bool inMenuUI = false;
	bool inDebugUI = false;
	bool inMapUI = false;
	bool inPauseUI = false;
};
