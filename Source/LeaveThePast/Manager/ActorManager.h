#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Actor/ActorBase.h"
#include "../Actor/MainActorInfo.h"
#include "../Actor/MinorActorInfo.h"
#include "../Actor/MassActorInfo.h"
#include "../Volume/VolumeBase.h"
#include "ActorManager.generated.h"

//管理演员和体积
UCLASS()
class LEAVETHEPAST_API UActorManager : public UObject
{
	GENERATED_BODY()
public:
	static UActorManager* GetInstance();

	void Init();

	//从场景配置中中加载演员到场景中
	UFUNCTION(BlueprintCallable)
	void LoadAllActorBySceneId(int sceneId);
	
	//将指定演员加载到场景中
	UFUNCTION(BlueprintCallable)
	AActorBase* LoadActorToSceneByActorInfo(UActorInfoBase* actorInfo);

	//通过演员InfoId获得演员，如果找到多个，则返回第一个
	UFUNCTION(BlueprintCallable)
	AActorBase* GetActorByInfoId(int actorInfoId);
	
	//通过演员Id获得演员信息
	UFUNCTION(BlueprintCallable)
	UActorInfoBase* GetActorInfoByInfoId(int actorInfoId);

	//通过演员Id获得新的演员信息，一般用于新建演员
	UFUNCTION(BlueprintCallable)
	UActorInfoBase* GetNewActorInfoByInfoId(int actorInfoId);

	//通过演员信息Id移除演员
	UFUNCTION(BlueprintCallable)
	int RemoveActorByInfoId(int actorInfoId);

	//获得场景中所有演员
	TMap<int, AActorBase*> GetAllActor();

	//获得场景中所有体积，只包括由管理类管理的体积，有一些在编辑场景中已存在的体积不会获得
	TArray<AVolumeBase*> GetAllVolume();

	//将体积加载到场景中
	UFUNCTION(BlueprintCallable)
	AVolumeBase* AddVolumeToSceneByVolumeInfo(FString volumeName,FVector position);

	//按体积的值移除体积
	UFUNCTION(BlueprintCallable)
	void RemoveVolumeByVolumeValue(FString volumeValue);
private:
	//加载主演
	void LoadMainActorInfo();
	//加载次演
	void LoadMinorActorInfo();
	//加载群演
	void LoadMassActorInfo();

	//加载所有合法体积
	void LoadAllIegalVolume();
	//加载合法指令
	void AddIegalVolume(AVolumeBase* volumeBase);

	static UActorManager* actorManager;

	FString mainActorRelativePath = TEXT("GameContent/Artres/Actor/MainActor.xml");
	FString minorActorRelativePath = TEXT("GameContent/Artres/Actor/MinorActor.xml");
	FString massActorRelativePath = TEXT("GameContent/Artres/Actor/MassActor.xml");

	UPROPERTY()
	TMap<int, UMainActorInfo*> mainActorInfoMap;
	UPROPERTY()
	TMap<int, UMinorActorInfo*> minorActorInfoMap;
	UPROPERTY()
	TMap<int, UMassActorInfo*> massActorInfoMap;

	UPROPERTY()
	TMap<int, AActorBase*> actorBaseByInfoIdMap;

	UPROPERTY()
	TMap<FString, AVolumeBase*> legalVolumeMap;
	UPROPERTY()
	TArray<AVolumeBase*> volumeList;
};
