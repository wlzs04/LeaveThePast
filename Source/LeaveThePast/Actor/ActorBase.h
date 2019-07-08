#pragma once

#include "CoreMinimal.h"
#include "XmlParser/Public/XmlFile.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ActorInfoBase.h"
#include "ActorBase.generated.h"

class UActionBase;

UCLASS()
class LEAVETHEPAST_API AActorBase : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AActorBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//执行指令
	UFUNCTION(BlueprintCallable)
	virtual void Execute(UActionBase* action);

	//开始表演
	UFUNCTION(BlueprintCallable)
	virtual void StartPerform();

	//设置角色信息
	void SetActorInfo(UActorInfoBase* newActorInfo);

	//设置角色信息
	UFUNCTION(BlueprintCallable)
	UActorInfoBase* GetActorInfo();

	//加载演员模型
	UFUNCTION(BlueprintCallable)
	void LoadModel();

	int GetActorId();

	bool IsPermanent();

	FVector GetDefaultPosition();
	FRotator GetDefaultRotation();

	UFUNCTION(BlueprintCallable)
	bool IsInTalking();

	void StartTalk();

	void StopTalk();

	//设置摄像机跟随
	void AddCameraFollow();

	//移除摄像机跟随
	void RemoveCameraFollow();

	void MoveForwardInputFunction(float value);
	void MoveRightInputFunction(float value);
	void TurnInputFunction(float value);
	void LookUpInputFunction(float value);

	void SetAccelerate(bool enableAccelerate);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
private:

	UPROPERTY()
	UActorInfoBase* actorInfo = nullptr;
	TArray<UActionBase*> actionList;

	bool isInTalking = false;//在谈话中

	//摄像机组件
	UPROPERTY()
	USpringArmComponent* springArmComponent = nullptr;
	UPROPERTY()
	UCameraComponent* cameraComponent = nullptr;

	int y = 0;
};
