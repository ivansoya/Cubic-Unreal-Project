// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EquipmentInteface.generated.h"

class UEquipmentItem;
class USkeletalMesh;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquipment : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BROWSEPROJECT_API IEquipment
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	bool EquipItemOnCharacter(UEquipmentItem* Item, ESlotStatus SlotStatus);

	UFUNCTION(BlueprintNativeEvent)
	bool SetSkeletalMeshAsCharacterPart(USkeletalMesh* SkeletalMesh, ESlotType Slot);
};
