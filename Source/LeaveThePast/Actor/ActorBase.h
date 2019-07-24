#pragma once

#include "CoreMinimal.h"
#include "XmlParser/Public/XmlFile.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "ActorInfoBase.h"
#include "ActorBase.generated.h"

class UActionBase;
class USoundBase;

UCLASS()
class LEAVETHEPAST_API AActorBase : public ACharacter
{
	GENERATED_BODY()
public:
	AActorBase();

	void InitByActorInfo();

	virtual void Tick(float DeltaTime) override;

	//执行指令
	UFUNCTION(BlueprintCallable)
	virtual void Execute(UActionBase* action);

	//设置角色信息
	void SetActorInfo(UActorInfoBase* newActorInfo);

	//设置角色信息
	UFUNCTION(BlueprintCallable)
	UActorInfoBase* GetActorInfo();

	//演员Id，唯一标志，只能设置一次
	void SetActorId(int newActorId);
	int GetActorId();

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

	TArray<FScriptRecorderInfo> GetInteractedScriptList();
	void AddinteractedScriptList(FScriptRecorderInfo scriptRecorder);

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
	TArray<UActionBase*> actionList;

	bool isInTalking = false;//在谈话中
	int actorId = 0;//演员唯一Id

	//摄像机组件
	UPROPERTY()
	USpringArmComponent* springArmComponent = nullptr;
	UPROPERTY()
	UCameraComponent* cameraComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* audioComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* interactedComponent = nullptr;

	TArray<FScriptRecorderInfo> interactedScriptList;
};
