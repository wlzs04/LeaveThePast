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

	//从场景中加载演员，一般用于测试阶段调整演员位置。
	//UFUNCTION(BlueprintCallable)
	//void LoadAllActorFromScene();

	//从场景配置中中加载演员到场景中
	UFUNCTION(BlueprintCallable)
	void LoadAllActorBySceneId(int sceneId);
	
	//将指定演员加载到场景中
	UFUNCTION(BlueprintCallable)
	AActorBase* LoadActorToSceneByActorInfo(UActorInfoBase* actorInfo);

	//通过演员Id获得演员
	UFUNCTION(BlueprintCallable)
	AActorBase* GetActorById(int actorId);

	//通过演员InfoId获得演员，如果找到多个，则返回第一个
	UFUNCTION(BlueprintCallable)
	AActorBase* GetActorByInfoId(int actorInfoId);
	
	//通过演员Id获得演员信息
	UFUNCTION(BlueprintCallable)
	UActorInfoBase* GetActorInfoByInfoId(int actorInfoId);

	//通过演员Id获得新的演员信息，一般用于新建演员
	UFUNCTION(BlueprintCallable)
	UActorInfoBase* GetNewActorInfoByInfoId(int actorInfoId);
	
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

	//通过actorId
	TMap<int, AActorBase*> actorBaseByIdMap;
	//通过actorInfoId
	TMap<int, AActorBase*> actorBaseByInfoIdMap;

	int actorIdUnique = 0;//唯一的演员Id
};
