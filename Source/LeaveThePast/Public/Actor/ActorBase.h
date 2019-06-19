#pragma once

#include "CoreMinimal.h"
#include "XmlParser/Public/XmlFile.h"
#include "GameFramework/Character.h"
#include <LeaveThePast\Public\Actor\ActorInfoBase.h>
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

	void SetActorInfo(UActorInfoBase* newActorInfo);

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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UActorInfoBase* actorInfo = nullptr;
	TArray<UActionBase*> actionList;
};
