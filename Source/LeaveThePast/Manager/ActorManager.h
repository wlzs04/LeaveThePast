#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Actor/ActorBase.h"
#include "../Actor/MainActorInfo.h"
#include "../Actor/MinorActorInfo.h"
#include "../Actor/MassActorInfo.h"
#include "ActorManager.generated.h"

UCLASS()
class LEAVETHEPAST_API UActorManager : public UObject
{
	GENERATED_BODY()
public:
	static UActorManager* GetInstance();

	void Init();

	//加载所有演员
	void LoadAllActorInfo();

	//将所有常驻演员加载到场景中
	void LoadAllPermanentActorToScene();

	//将指定演员加载到场景中
	UFUNCTION(BlueprintCallable)
	AActorBase* LoadActorToSceneById(int actorId);

	//通过演员Id获得演员
	UFUNCTION(BlueprintCallable)
	AActorBase* GetActorById(int actorId);

	//通过演员Id获得演员信息
	UFUNCTION(BlueprintCallable)
	UActorInfoBase* GetActorInfoById(int actorId);
private:
	//加载主演
	void LoadMainActorInfo();
	//加载次演
	void LoadMinorActorInfo();
	//加载群演
	void LoadMassActorInfo();

	static UActorManager* actorManager;

	FString mainActorRelativePath = TEXT("GameContent/Artres/Actor/MainActor.xml");
	FString minorActorRelativePath = TEXT("GameContent/Artres/Actor/MinorActor.xml");
	FString massActorRelativePath = TEXT("GameContent/Artres/Actor/MassActor.xml");

	TMap<int, UMainActorInfo*> mainActorInfoMap;
	TMap<int, UMinorActorInfo*> minorActorInfoMap;
	TMap<int, UMassActorInfo*> massActorInfoMap;

	TMap<int, AActorBase*> actorBaseMap;
	TSubclassOf<AActor> BPMyActorClass;
};
