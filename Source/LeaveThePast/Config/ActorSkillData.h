#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputCoreTypes.h"
#include "ActorSkillData.generated.h"

class FXmlNode;

//技能数据结构体
USTRUCT(BlueprintType)
struct FSkillData
{
	GENERATED_USTRUCT_BODY()
public:
	FSkillData()
	{
		skillId = 0;
		proficiency = 0;
	}

	UPROPERTY(BlueprintReadWrite)
	int skillId;
	UPROPERTY(BlueprintReadWrite)
	FKey key;
	UPROPERTY(BlueprintReadWrite)
	int proficiency;
};

//演员技能数据类
UCLASS()
class LEAVETHEPAST_API UActorSkillData : public UObject
{
	GENERATED_BODY()

public:
	void LoadFromXmlNode(FXmlNode* xmlNode);
	
	//通过技能Id获得对应技能信息
	FSkillData GetSkillDataById(int skillId);

	//通过key获得对应技能信息
	FSkillData GetSkillDataByKey(FKey key);

	//获得技能Map
	TMap<int, FSkillData> GetSkillDataMap();

private:
	TMap<int, FSkillData> skillDataMap;
};
