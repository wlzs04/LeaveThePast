#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HelpManager.generated.h"

class UTexture2D;

UCLASS()
class LEAVETHEPAST_API UHelpManager : public UObject
{
	GENERATED_BODY()
public:
	static UHelpManager* GetInstance();

	void Init();

	static FVector ConvertFStringToFVector(FString value);
	static FRotator ConvertFStringToFRotator(FString value);
	static FString ConvertToFString(FVector value);
	static FString ConvertToFString(FRotator value);
	static FString ConvertToFString(FTimespan value);
	static FTimespan ConvertFStringToFTimespan(FString value);

	//加载本地图片
	static UTexture2D* LoadTexture2D(FString path, bool& isValid, int32& outWidth, int32& outHeight);
private:
	static UHelpManager* helpManager;
};
