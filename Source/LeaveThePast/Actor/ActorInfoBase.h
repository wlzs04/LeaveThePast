#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "Property/PropertyBase.h"
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

UCLASS()
class LEAVETHEPAST_API UActorInfoBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Load(FXmlNode* xmlNode);

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
	TMap<FString, UPropertyBase*> GetPropertyMap();

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

	TMap<FString,UPropertyBase*> propertyMap;//属性列表
	TArray<FChat> chatList;//闲话列表
};