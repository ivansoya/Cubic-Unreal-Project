// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BrowseProject/General/Items/System/ItemEnums.h"
#include "Equipment.generated.h"

// Делегаты для экипировки
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipItemSignature, const UEquipmentItem*, EquipItem, ESlotType, Slot);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWithdrawItemSignature, const UEquipmentItem*, WithdrawSlot, ESlotType, Slot);

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
	bool GetStatsForRequirements(const int32& Strength, const int32& Dexterity, const int32& Intelligence, const int32& Endurance, const TArray<EWeaponType>& WeaponStances);

	UFUNCTION(BlueprintNativeEvent)
	bool EquipItemOnCharacter(const UEquipmentItem* Item, ESlotType Slot);

	UFUNCTION(BlueprintNativeEvent)
	bool SetWeaponMeshAtSocket(UStaticMesh* WeaponMesh, const FName& WeaponSocket, bool IsRight);

	UFUNCTION(BlueprintNativeEvent)
	bool WithdrawItemFromCharacterSlot(ESlotType Slot);

	UFUNCTION(BlueprintNativeEvent)
	bool SetSkeletalMeshAsCharacterPart(USkeletalMesh* SkeletalMesh, ESlotType Slot);

	UFUNCTION(BlueprintNativeEvent)
	bool SetBasicSkeletalMeshAtSlot(ESlotType Slot);

	virtual FOnEquipItemSignature& GetOnEquipItemSignature() = 0;

	virtual FOnWithdrawItemSignature& GetOnWithdrawItemSignature() = 0;

};
