#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <LeaveThePast\Public\Actor\ActorBase.h>
#include <LeaveThePast\Public\Actor\MainActorInfo.h>
#include <LeaveThePast\Public\Actor\MinorActorInfo.h>
#include <LeaveThePast\Public\Actor\MassActorInfo.h>
#include "ActorManager.generated.h"

UCLASS()
class LEAVETHEPAST_API UActorManager : public UObject
{
	GENERATED_BODY()
public:
	UActorManager();

	//加载所有演员
	void LoadAllActorInfo();

	//将所有常驻演员加载到场景中
	void LoadAllPermanentActorToScene();

	//将指定演员加载到场景中
	AActorBase* LoadActorToSceneById(int actorId);

	//通过演员Id获得演员
	AActorBase* GetActorById(int actorId);

	//通过演员Id获得演员信息
	UActorInfoBase* GetActorInfoById(int actorId);
private:
	//加载主演
	void LoadMainActorInfo();
	//加载次演
	void LoadMinorActorInfo();
	//加载群演
	void LoadMassActorInfo();

	FString mainActorRelativePath = TEXT("GameContent/Artres/Actor/MainActor.xml");
	FString minorActorRelativePath = TEXT("GameContent/Artres/Actor/MinorActor.xml");
	FString massActorRelativePath = TEXT("GameContent/Artres/Actor/MassActor.xml");

	TMap<int, UMainActorInfo*> mainActorInfoMap;
	TMap<int, UMinorActorInfo*> minorActorInfoMap;
	TMap<int, UMassActorInfo*> massActorInfoMap;

	TMap<int, AActorBase*> actorBaseMap;
	TSubclassOf<AActor> BPMyActorClass;
};
