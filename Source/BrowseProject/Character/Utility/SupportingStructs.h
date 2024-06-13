// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrowseProject/General/Items/System/ItemEnums.h"
#include "CoreMinimal.h"
#include "SupportingStructs.generated.h"

class UEquipmentItem;

UENUM(BlueprintType)
enum class ESetAtStatus : uint8
{
	NULL_ITEM_SET = 0 UMETA(DisplayName = "Setting Item is Null"),
	AT_SLOT_NONE_ITEM = 1 UMETA(DisplayName = "There is Mo Item St Slot"),
	RETURNING_ITEM = 2 UMETA(DisplayName = "Has Wisdrawed Item"),
	NONE_SLOT = 3 UMETA(DisplayName = "There is No Existing Slot"),
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FSetAtStatus
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Withdraw Item"))
	UEquipmentItem* WithdrawItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Operation Status"))
	ESetAtStatus Status;
};

/// <summary>
/// Структура слотов в экипировки
/// </summary>
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FEquipmentSlot
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Ref of Item Object"))
	UEquipmentItem* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Slot Status"))
	ESlotStatus Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Default Slot Status"))
	ESlotStatus DefaultStatus;
};