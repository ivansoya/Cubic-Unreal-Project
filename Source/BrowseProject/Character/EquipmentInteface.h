// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SupportingStructs.h"
#include "EquipmentInteface.generated.h"

// Делегаты для обычной экипировки
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipItemSignature, FEquipmentSlot, EquipItem, ESlotType, Slot);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWithdrawItemSignature, FEquipmentSlot, WithdrawSlot, ESlotType, Slot);

// Делегаты для магических кубиков
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPutMagicDiceInPocketSignature, UDice*, Dice, EDice, Slot);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTakeOffDiceFromPocketSignature, UDice*, Dice, EDice, Slot);

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
	bool EquipItemOnCharacter(UEquipmentItem* Item, ESlotType Slot);

	UFUNCTION(BlueprintNativeEvent)
	bool WithdrawItemFromCharacterSlot(ESlotType Slot);

	UFUNCTION(BlueprintNativeEvent)
	bool SetSkeletalMeshAsCharacterPart(USkeletalMesh* SkeletalMesh, ESlotType Slot);

	UFUNCTION(BlueprintNativeEvent)
	bool SetBasicSkeletalMeshAtSlot(ESlotType Slot);

	UFUNCTION(BlueprintNativeEvent)
	bool ChangeSlotStatus(ESlotType Slot, ESlotStatus Status);

	UFUNCTION(BlueprintNativeEvent)
	bool ReturnDefaultSlotStatus(ESlotType Slot, ESlotStatus Status);

	UFUNCTION(BlueprintNativeEvent)
	UDice* GetDiceFromSlot(EDice Slot);

	UFUNCTION(BlueprintNativeEvent)
	bool PutDiceInPocket(EDice Slot, UDice* Dice);

	UFUNCTION(BlueprintNativeEvent)
	bool TakeOffDiceFromPocket(EDice Slot);

	//UFUNCTION(BlueprintNativeEvent)
	virtual FEquipmentSlot* GetSlotStructure(ESlotType Slot) = 0;

	virtual FOnEquipItemSignature& GetOnEquipItemSignature() = 0;

	virtual FOnWithdrawItemSignature& GetOnWithdrawItemSignature() = 0;

	virtual FOnPutMagicDiceInPocketSignature& GetOnPutMagicDiceInPocketSignature() = 0;

	virtual FOnTakeOffDiceFromPocketSignature& GetOnTakeOffDiceFromPocketSignature() = 0;
};
