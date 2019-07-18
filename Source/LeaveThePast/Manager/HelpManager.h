#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HelpManager.generated.h"

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
private:
	static UHelpManager* helpManager;
};
