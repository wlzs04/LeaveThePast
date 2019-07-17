#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "../Config/Recorder/SceneRecorder.h"
#include "ActorInfoBase.generated.h"

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

UCLASS()
class LEAVETHEPAST_API UActorInfoBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Load(FXmlNode* xmlNode);

	//从演员信息中拷贝信息
	void CopyData(UActorInfoBase* actorInfo);

	//从场景演员信息中覆盖信息
	void CoverData(FSceneActorInfo sceneActorInfo);

	int GetActorId();

	UFUNCTION(BlueprintCallable)
	FString GetActorName();

	UFUNCTION(BlueprintCallable)
	int GetActorType();

	UFUNCTION(BlueprintCallable)
	FString GetActorTypeValue();

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

	//随机获得一句闲话
	FChat GetRandomChat();
private:
	int actorId = 0;//演员的Id
	FString actorName = TEXT("未命名演员");//演员名称
	int actorType = 0;//演员类型 0 普通 1 商店
	FString actorTypeValue = TEXT("");//演员类型的参数
	FString description = TEXT("无描述。");//演员描述
	FString modelName = TEXT("");//演员模型的名称
	FString modelRootPath = TEXT("");//演员模型的根路径
	FVector defaultPosition = FVector(0, 0, 0);//默认位置
	FRotator defaultRotation = FRotator(0, 0, 0);//默认角度
	FString headImagePath = TEXT("GameContent/Resource/Others/Image/Unknown.jpg");

	TMap<FString,FPropertyBase> propertyMap;//属性列表
	TArray<FChat> chatList;//闲话列表
};
