// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "RotateAction.generated.h"

/**
 * 
 */
UCLASS()
class LEAVETHEPAST_API URotateAction : public UActionBase
{
	GENERATED_BODY()
public:
	URotateAction();
protected:
	//加载内容
	virtual void Load(FXmlNode* xmlNode) override;
	virtual void Update() override;
	virtual void ExecuteReal() override;

private:
	float actionTime = 1;
	//转身角度，默认Z方向，人正常转身的方向
	float value = 90;

	APawn* currentPlayer = nullptr;
	float currentTime = 0;
	float lastTime = 0;
	float startTime = 0;
};
