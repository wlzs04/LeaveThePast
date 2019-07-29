#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeData.h"
#include "UserData.generated.h"

class FXmlNode;

USTRUCT(BlueprintType)
struct FSaveActorInfo
{
	GENERATED_USTRUCT_BODY()

	FSaveActorInfo()
	{
		actorId = 0;
	}

	void LoadFromXmlNode(FXmlNode* xmlNode);

	int actorId;
	FVector position;
	FRotator rotation;

	TArray<FScriptRecorderInfo> scriptRecorderList;
};

USTRUCT(BlueprintType)
struct FSaveVolumeInfo
{
	GENERATED_USTRUCT_BODY()

	FSaveVolumeInfo(){}

	void LoadFromXmlNode(FXmlNode* xmlNode);

	FString volumeType;
	FVector position;
	FString value;
};

USTRUCT(BlueprintType)
struct FSaveSectionInfo
{
	GENERATED_USTRUCT_BODY()

	FSaveSectionInfo()
	{
		id = 0;
		state = 0;
	}

	int id;
	int state;//0 未开始 1 进行中 2 完成 3 失败
	TMap<int, int> paragraphMap;
};

USTRUCT(BlueprintType)
struct FSaveChapterInfo
{
	GENERATED_USTRUCT_BODY()

	FSaveChapterInfo()
	{
		state = 0;
	}

	FString name;
	int state;//0 未开始 1 进行中 2 完成 3 失败
	TMap<int, FSaveSectionInfo> sectionMap;
};

USTRUCT(BlueprintType)
struct FScriptRecorderInfo
{
	GENERATED_USTRUCT_BODY()

	FScriptRecorderInfo()
	{
		sectionId = 0; 
		paragraphId = 0;
	}

	FScriptRecorderInfo(FString newChapter, int newSectionId, int newParagraphId)
	{
		chapter = newChapter;
		sectionId = newSectionId;
		paragraphId = newParagraphId;
	}

	bool operator == (const FScriptRecorderInfo& anotherRecorderInfo)
	{
		return (chapter == anotherRecorderInfo.chapter) &&
			sectionId == anotherRecorderInfo.sectionId &&
			paragraphId == anotherRecorderInfo.paragraphId;
	}

	void LoadFromXmlNode(FXmlNode* xmlNode);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString chapter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int sectionId = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int paragraphId = 0;
};

UCLASS(BlueprintType)
class LEAVETHEPAST_API UUserData : public UObject
{
	GENERATED_BODY()
public:
	UUserData();

	void Load();

	void Save();

	//设置初始存档
	void SetInitData();

	UFUNCTION(BlueprintCallable)
	FTimeData GetGameTimeData();

	//设置游戏内时间
	UFUNCTION(BlueprintCallable)
	void SetGameTime(int hour, int minute, int second);

	void Tick(float secondTime);

	UFUNCTION(BlueprintCallable)
	void SetIsFixedTime(bool newIsFixedTime);
	UFUNCTION(BlueprintCallable)
	bool GetIsFixedTime();

	UFUNCTION(BlueprintCallable)
	void SetGameAndRealTimeRate(float newGameAndRealTimeRate);
	UFUNCTION(BlueprintCallable)
	float GetGameAndRealTimeRate();

	//场景
	UFUNCTION(BlueprintCallable)
	void SetSceneId(int newSceneId);
	UFUNCTION(BlueprintCallable)
	int GetSceneId();

	//可控演员列表
	TArray<int> GetCanControlActorList();

	//添加可控演员
	void AddControlActor(int actorInfoId);

	//移除可控演员
	void RemoveControlActor(int actorInfoId);

	//场景演员列表
	TArray<FSaveActorInfo> GetSceneActorList();

	//场景体积列表
	TArray<FSaveVolumeInfo> GetSceneVolumeList();
	
	//获得物品map
	UFUNCTION(BlueprintCallable)
	TMap<int, int> GetItemMap();

	//获得物品数量
	UFUNCTION(BlueprintCallable)
	int GetItemNumberById(int itemId);

	//添加物品
	UFUNCTION(BlueprintCallable)
	void AddItem(int itemId,int number);

	//减少物品，返回实际减少的个数
	UFUNCTION(BlueprintCallable)
	int ReduceItem(int itemId, int number);

	//设置物品数量
	UFUNCTION(BlueprintCallable)
	void SetItemNumber(int itemId, int number);

	//获得钱数 根据物品中铜钱、银两等值钱物品进行换算
	UFUNCTION(BlueprintCallable)
	int GetMoney();

	//消耗钱
	UFUNCTION(BlueprintCallable)
	void ReduceMoney(int money);

	//获得剧本Map
	UFUNCTION(BlueprintCallable)
	TMap<FString, FSaveChapterInfo> GetChapterMap();

	void SetChapterState(FString scriptName, int state);
	void SetSectionState(FString scriptName, int sectionId, int state);
	void SetParagraphState(FString scriptName, int sectionId, int paragrapgId, int state);

	//获得玩家即将运行的剧本列表
	UFUNCTION(BlueprintCallable)
	TArray<FScriptRecorderInfo> GetNextScriptList();

	//添加玩家即将运行的剧本
	UFUNCTION(BlueprintCallable)
	void AddNextScript(FScriptRecorderInfo newScriptRecorderInfo);

	//移除玩家即将运行的剧本
	UFUNCTION(BlueprintCallable)
	void RemoveNextScript(FScriptRecorderInfo newScriptRecorderInfo);
protected:
	//保存路径
	FString savePath;

	FTimeData gameTimeData;

	bool isFixedTime = false;//是否固定时间
	float gameAndRealTimeRate = 1;
	int sceneId = 10001;//角色所在场景Id
	TArray<int> canControlActorList;//可控演员列表
	TArray<FSaveActorInfo> sceneActorList;//场景演员列表
	TArray<FSaveVolumeInfo> sceneVolumeList;//场景体积列表
	
	TMap<int, int> itemMap;

	TMap<FString, FSaveChapterInfo> chapterMap;//剧本状态

	TArray<FScriptRecorderInfo> nextScriptList;//玩家即将运行的剧本列表，在游戏开始后立即执行
};
