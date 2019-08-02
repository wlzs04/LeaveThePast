#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "VolumeBase.generated.h"

//体积基类
UCLASS()
class LEAVETHEPAST_API AVolumeBase : public AActor
{
	GENERATED_BODY()
public:	
	AVolumeBase();

	UFUNCTION(BlueprintCallable)
	FString GetVolumeName();

	UFUNCTION(BlueprintCallable)
	bool GetCanSave();

	UFUNCTION(BlueprintCallable)
	virtual void LoadFromString(FString volumeValueString);

	UFUNCTION(BlueprintCallable)
	virtual FString GetVolumeValue();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void VolumeBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void VolumeBeginOverlapEventReal(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* nearbyComponent = nullptr;

	FString volumeName = TEXT("未命名体积");
	bool canSave = false;//是否保存到玩家存档中
};
