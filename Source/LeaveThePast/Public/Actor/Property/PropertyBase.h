#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "PropertyBase.generated.h"

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

UCLASS()
class LEAVETHEPAST_API UPropertyBase : public UObject
{
	GENERATED_BODY()
public:
	void SetInfo(FString newPropertyName, FString newPropertyValue);
	FString GetPropertyValue();
	FString GetPropertyName();
	PropertyEnum GetPropertyType();
private:
	PropertyEnum propertyEnum = PropertyEnum::Unknown;
	FString propertyName = TEXT("未命名");
	FString propertyValue = TEXT("未知值");
};
