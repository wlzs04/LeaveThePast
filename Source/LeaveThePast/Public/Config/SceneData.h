#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlParser/Public/XmlFile.h"
#include "SceneData.generated.h"

UCLASS()
class LEAVETHEPAST_API USceneData : public UObject
{
	GENERATED_BODY()
public:
	USceneData();

	void Load(FXmlNode* xmlNode);

	UFUNCTION(BlueprintCallable)
	int GetId();

	UFUNCTION(BlueprintCallable)
	FString GetSceneName();

	UFUNCTION(BlueprintCallable)
	FVector2D GetRangeX();

	UFUNCTION(BlueprintCallable)
	TArray<USceneData*> GetSceneDataList();
private:
	//场景Id
	int id = 0;
	//场景名称
	FString sceneName = TEXT("未命名");
	//场景中心
	FVector2D center = FVector2D(0, 0);
	//场景范围
	FVector2D rangeX = FVector2D(0,100);
	//子场景
	TArray<USceneData*> sceneDataList;
};
