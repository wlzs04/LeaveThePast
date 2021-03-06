#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Config/UserData.h"
#include "ActorInfoBase.h"
#include "ActorBase.generated.h"

class UActionBase;
class USoundCue;
class UAudioComponent;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UBlackboardComponent;
class UBehaviorTree;
class AMainAIController;

//演员基类
UCLASS()
class LEAVETHEPAST_API AActorBase : public ACharacter
{
	GENERATED_BODY()
public:
	AActorBase();

	void InitByActorInfo();

	virtual void Tick(float DeltaTime) override;

	//设置角色信息
	void SetActorInfo(UActorInfoBase* newActorInfo);

	//设置角色信息
	UFUNCTION(BlueprintCallable)
	UActorInfoBase* GetActorInfo();

	UFUNCTION(BlueprintCallable)
	bool IsInTalking();

	/*UFUNCTION(BlueprintCallable)
	bool IsInAttack();

	UFUNCTION(BlueprintCallable)
	bool IsAttackKeyDown();*/

	void StartTalk();

	void StopTalk();

	void StartPlayVoiceSound(USoundCue* soundBase);

	//设置摄像机跟随
	void AddCameraFollow();

	//移除摄像机跟随
	void RemoveCameraFollow();

	void MoveForwardInputFunction(float value);
	void MoveRightInputFunction(float value);
	void TurnInputFunction(float value);
	void LookUpInputFunction(float value);

	UFUNCTION(BlueprintCallable)
	void SetAccelerate(bool enableAccelerate);

	TArray<AActor*> GetInteractedActor();

	TArray<FScriptItemData> GetInteractedScriptList();
	void AddInteractedScript(FScriptItemData scriptItemData);
	void RemoveInteractedScript(FScriptItemData scriptItemData);

	//使用技能
	UFUNCTION(BlueprintCallable)
	void UseSkillByKey(FKey key);
	////攻击
	//UFUNCTION(BlueprintCallable)
	//void AttackPress();
	////攻击
	//UFUNCTION(BlueprintCallable)
	//void AttackRelease();
	////重新计算连招，一般在攻击结束后调用
	//UFUNCTION(BlueprintCallable)
	//void ResetAttackCombo();
	////获得当前为第几次攻击连招
	//UFUNCTION(BlueprintCallable)
	//void SetAttackComboIndex(int newAttackComboIndex);
	////获得当前为第几次攻击连招
	//UFUNCTION(BlueprintCallable)
	//int GetAttackComboIndex();

	//设置被AI控制
	void AddControlByAI();
	//设置被AI控制
	void RemoveControlByAI();

	//行为树
	UBehaviorTree* GetBehaviorTree();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int actorIdForEditor = 0;
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
private:
	//加载演员模型
	UFUNCTION(BlueprintCallable)
	void LoadModel();

	UFUNCTION()
	void ActorBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ActorEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY()
	UActorInfoBase* actorInfo = nullptr;

	bool isInTalking = false;//在谈话中
	//bool isInAttack = false;//在战斗动作中，有一些战斗动作不允许角色移动
	//bool isAttackKeyDown = false;//战斗按键是否点击

	int attackComboIndex = -1;//一般用于攻击连招

	//摄像机组件
	UPROPERTY()
	USpringArmComponent* springArmComponent = nullptr;
	UPROPERTY()
	UCameraComponent* cameraComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* audioComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* interactComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* nearbyComponent = nullptr;

	TArray<FScriptItemData> interactedScriptList;//动态添加的交互剧本

	int currentActionIndex = 0;
	bool executeNearbyAction = false;//执行附近指令
	bool nearbyActionIsCompleted = true;//附近指令是否执行完

	UPROPERTY()
	UBehaviorTree* behaviorTree = nullptr;
	UPROPERTY()
	AMainAIController* mainAIController = nullptr;
};
