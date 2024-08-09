// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetInfoInterface.generated.h"

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FTargetDisplayInfo
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TargetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentDurability;
};

// Делегат, определяющий событие показа полоски жизни моба
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayTargetBarSignature, const FTargetDisplayInfo&, TargetInfo);
// Делегат, отвечающий за событие скрытые полоски жизни моба
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideTargetBarSignature);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetInfo : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BROWSEPROJECT_API ITargetInfo
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void SetTargetInfo(const FTargetDisplayInfo& TargetInfo);

	UFUNCTION(BlueprintNativeEvent)
	void HideTargetInfo();

	UFUNCTION(BlueprintNativeEvent)
	void ChangeHealthValue(int32 CurrentHealth, int32 MaxHealth);

	UFUNCTION(BlueprintNativeEvent)
	void ChangeDurabilityValue(int32 CurrentDurability, int32 MaxDurability);
};
