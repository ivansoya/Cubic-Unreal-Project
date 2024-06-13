// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BrowseProject/General/Items/System/ItemEnums.h"
#include "Inventory.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddItemToInventorySignature, UBasicItem*, AddedItem);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoveItemFromInventorySignature, UBasicItem*, RemovedItem);

class UEquipmentItem;
class UBasicItem;

UENUM(BlueprintType)
enum class EStatusOnAdd : uint8 {

	ADDED = 0 UMETA(DisplayName = "Successfully Added"),
	ITEM_EXISTS = 1 UMETA(DisplayName = "Item Already has Added"),
	ALL_SLOTS_ENGAGED = 2 UMETA(DisplayName = "No More Space for Adding"),
	ID_ERROR = 3 UMETA(DisplayName = "Error with ID matching"),
	NULL_ERROR = 4 UMETA(DisplayName = "Item is nullptr"),
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventory: public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BROWSEPROJECT_API IInventory
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Удаляет предмет экипировки из инвентаря по поиску
	UFUNCTION(BlueprintNativeEvent)
	void RemoveEquipItemFromInventoryByFind(UEquipmentItem* RemoveItem);

	// Добавляет предмет экипировки в инвентарь
	UFUNCTION(BlueprintNativeEvent)
	EStatusOnAdd AddEquipItemToInventory(UEquipmentItem* EquipItem);

	// Добавляет складываемый предмет в инвентарь
	UFUNCTION(BlueprintNativeEvent)
	EStatusOnAdd AddBasicItemToInventory(UBasicItem* BasicItem);

	virtual FOnAddItemToInventorySignature& GetOnAddItemToInventorySignature() = 0;

	virtual FOnRemoveItemFromInventorySignature& GetOnRemoveItemFromInventorySignature() = 0;
};
