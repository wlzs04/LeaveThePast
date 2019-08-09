#include "MainAIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardData.h"
#include "ActorBase.h"
#include "DirectorActor.h"

AMainAIController::AMainAIController()
{
	behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	blackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

}

void AMainAIController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);

	AActorBase* actor = Cast<AActorBase>(Pawn);

	if (actor)
	{
		if (actor->GetBehaviorTree()->BlackboardAsset)
		{
			blackboardComponent->InitializeBlackboard(*(actor->GetBehaviorTree()->BlackboardAsset));
		}

		behaviorTreeComponent->StartTree(*actor->GetBehaviorTree());
	}
}

void AMainAIController::SetTagetActor(AActor* actor)
{
	blackboardComponent->SetValueAsObject(TEXT("TargetActor"), actor);
	blackboardComponent->SetValueAsBool(TEXT("TestBool"), true);
}
