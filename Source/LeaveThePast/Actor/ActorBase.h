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

	void SetAccelerate(bool enableAccelerate);

	TArray<AActor*> GetInteractedActor();

	TArray<FScriptItemData> GetInteractedScriptList();
	void AddInteractedScript(FScriptItemData scriptItemData);
	void RemoveInteractedScript(FScriptItemData scriptItemData);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int actorIdForEditor = 0;
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
private:
	//加载演员模型
	UFUNCTION(BlueprintCallable)
	void LoadModel();

	UPROPERTY()
	UActorInfoBase* actorInfo = nullptr;

	bool isInTalking = false;//在谈话中

	//摄像机组件
	UPROPERTY()
	USpringArmComponent* springArmComponent = nullptr;
	UPROPERTY()
	UCameraComponent* cameraComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* audioComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* interactedComponent = nullptr;

	TArray<FScriptItemData> interactedScriptList;
};
