#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DirectorActor.generated.h"

class AActorBase;
class USoundCue;
class UAudioComponent;
class USphereComponent;

//导演类，受玩家控制
UCLASS()
class LEAVETHEPAST_API ADirectorActor : public APawn
{
	GENERATED_BODY()

public:
	ADirectorActor();

	static ADirectorActor* GetInstance();

	//初始化场景演员、可控演员和体积，从用户存档内读取
	void InitActor();

	//添加演员到可控演员列表中
	UFUNCTION(BlueprintCallable)
	void AddCanControlActorByInfoId(int actorInfoId);

	//从可控演员列表中移除指定演员
	UFUNCTION(BlueprintCallable)
	void RemoveCanControlActorByInfoId(int actorInfoId);

	//通过id设置当前控制演员
	UFUNCTION(BlueprintCallable)
	void SetControlActorById(int actorId);

	//通过index设置当前控制演员
	UFUNCTION(BlueprintCallable)
	void SetControlActorByIndex(int index);

	//设置当前控制演员
	UFUNCTION(BlueprintCallable)
	void SetControlActor(AActorBase* actor);

	//通过当前控制演员
	UFUNCTION(BlueprintCallable)
	AActorBase* GetCurrentControlActor();

	//通过当前控制演员在列表中的位置
	UFUNCTION(BlueprintCallable)
	int GetCurrentControlActorIndex();

	//通过可控演员列表
	UFUNCTION(BlueprintCallable)
	TArray<AActorBase*> GetCanControlActorList();

	//播放背景音乐
	void StartPlayBGMSound(USoundCue* soundBase);

	//目的地位置
	UFUNCTION(BlueprintCallable)
	void SetDestination(FVector newDestinationPosition);
	UFUNCTION(BlueprintCallable)
	FVector GetDestination();

	//是否可控
	UFUNCTION(BlueprintCallable)
	bool GetCanControl();
	UFUNCTION(BlueprintCallable)
	void SetCanControl(bool newCanControl);

	void SetCanControlMove(bool newCanControlMove);
	void SetCanControlView(bool newCanControlView);

	//添加只可控UI的层数
	void AddCanOnlyControlUINumber();
	//减少只可控UI的层数
	void RemoveCanOnlyControlUINumber();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveForwardInputFunction(float value);
	void MoveRightInputFunction(float value);
	void TurnInputFunction(float value);
	void LookUpInputFunction(float value);

	void ChangeControlActorInputFunction();
	void StartAccelerateInputFunction();
	void StopAccelerateInputFunction();
	void InteractedInputFunction();

	void SystemInputFunction();
	void DebugInputFunction();
	void MapInputFunction();

	void SkillInputFunction(FKey key);
	
	static ADirectorActor* directorActor;
	
	UPROPERTY()
	UAudioComponent* audioComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* interactedComponent = nullptr;

	UPROPERTY()
	TArray<AActorBase*> canControlActorList;
	UPROPERTY()
	AActorBase* currentControlActor = nullptr;
	int currentControlActorIndex = 0;

	FVector destinationPosition = FVector(0, 0, 0);

	bool canControl = true;//判断是否可以接受输入，一般用于剧情中禁止玩家输入
	bool canControlMove = true;//玩家是否可以控制移动
	bool canControlView = true;//玩家是否可以控制视角

	int canOnlyControlUINumber = 0;//玩家只能控制UI不能控制演员，因为UI可能有多层，所以使用int
};
