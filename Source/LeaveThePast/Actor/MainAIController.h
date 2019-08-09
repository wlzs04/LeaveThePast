#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MainAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class APawn;

UCLASS()
class LEAVETHEPAST_API AMainAIController : public AAIController
{
	GENERATED_BODY()
public:

	AMainAIController();

	void SetTagetActor(AActor* actor);
protected:
	virtual void OnPossess(APawn* Pawn) override;//4.22以后使用OnPossess代替Possess

	UBehaviorTreeComponent* behaviorTreeComponent;
	UBlackboardComponent* blackboardComponent;
};
