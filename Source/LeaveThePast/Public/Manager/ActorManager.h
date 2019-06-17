// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <LeaveThePast\Public\Actor\MainActor.h>
#include <LeaveThePast\Public\Actor\MassActor.h>
#include "ActorManager.generated.h"

/**
 * 
 */
UCLASS()
class LEAVETHEPAST_API UActorManager : public UObject
{
	GENERATED_BODY()
public:
	//加载所有演员
	void LoadAllActor();
private:
	//加载主演
	void LoadMainActor();
	//加载群演
	void LoadMassActor();

	FString mainActorRelativePath = TEXT("GameContent/Artres/Actor/MainActor.xml");
	FString massActorRelativePath = TEXT("GameContent/Artres/Actor/MassActor.xml");

	TMap<int, AMainActor*> mainActorMap;
	TMap<int, AMassActor*> massActorMap;
};
