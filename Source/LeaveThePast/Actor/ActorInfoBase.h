#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Config/UserData.h"
#include "../Action/ActionBase.h"
#include "../Config/Recorder/SceneRecorder.h"
#include "ActorInfoBase.generated.h"

class FXmlNode;
class USceneActorData;

//说话结构体
USTRUCT()
struct FChat
{
	GENERATED_USTRUCT_BODY()

	FString text;
	FString voicePath;

	FChat()
	{
		text = TEXT("无");
		voicePath = TEXT("");
	}

	FChat(FString newText, FString newVoicePath)
	{
		text = newText;
		voicePath = newVoicePath;
	}
};

//演员属性类型
UENUM(BlueprintType)
enum class PropertyEnum :uint8
{
	Unknown UMETA(DisplayName = "未知"),
	Attact UMETA(DisplayName = "攻击力"),
	Defense UMETA(DisplayName = "防御力"),
	Speed UMETA(DisplayName = "速度"),
	Life UMETA(DisplayName = "生命值"),
	Power UMETA(DisplayName = "能力值"),
};

//演员属性结构体
USTRUCT(BlueprintType)
struct FPropertyBase
{
	GENERATED_USTRUCT_BODY()

	FPropertyBase()
	{
		propertyName = TEXT("未命名");
		propertyValue = 0;
		propertyEnum = PropertyEnum::Unknown;
	}

	UPROPERTY(BlueprintReadWrite)
	PropertyEnum propertyEnum;
	UPROPERTY(BlueprintReadWrite)
	FString propertyName;
	UPROPERTY(BlueprintReadWrite)
	float propertyValue;
};

//演员信息基类
UCLASS()
class LEAVETHEPAST_API UActorInfoBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Load(FXmlNode* xmlNode);

	//从演员信息中拷贝信息
	void CopyData(UActorInfoBase* actorInfo);

	//从场景演员信息中覆盖信息
	void CoverData(USceneActorData* sceneActorData);
	
	int GetActorId();

	UFUNCTION(BlueprintCallable)
	void SetActorName(FString newActorName);
	
	UFUNCTION(BlueprintCallable)
	FString GetActorName();

	UFUNCTION(BlueprintCallable)
	FString GetHeadImagePath();

	FString GetModelName();
	FString GetModelRootPath();

	FVector GetDefaultPosition();
	FRotator GetDefaultRotation();

	UFUNCTION(BlueprintCallable)
	float GetPropertyValue(FString propertyName);

	UFUNCTION(BlueprintCallable)
	TMap<FString, FPropertyBase> GetPropertyMap();

	UFUNCTION(BlueprintCallable)
	TArray<UActionBase*> GetInteractedActionList();

	UFUNCTION(BlueprintCallable)
	TArray<UActionBase*> GetNearbyActionList();
private:
	int actorId = 0;//演员的Id
	FString actorName = TEXT("未命名演员");//演员名称
	FString description = TEXT("无描述。");//演员描述
	FString modelName = TEXT("");//演员模型的名称
	FString modelRootPath = TEXT("");//演员模型的根路径
	FVector defaultPosition = FVector(0, 0, 0);//默认位置
	FRotator defaultRotation = FRotator(0, 0, 0);//默认角度
	FString headImagePath = TEXT("GameContent/Resource/Others/Image/Unknown.jpg");

	TMap<FString, FPropertyBase> propertyMap;//属性列表

	UPROPERTY()
	TArray<UActionBase*> interactedActionList;//玩家与此演员交互执行的指令列表
	UPROPERTY()
	TArray<UActionBase*> nearbyActionList;//玩家靠近此演员执行的指令列表
};
