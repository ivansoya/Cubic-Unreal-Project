// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Items/System/ItemEnums.h"
#include "BrowseProject/General/Items/System/Affixes.h"
#include "BrowseProject/General/FIcon.h"
#include "BrowseProject/General/Items/System/Rarity.h"
#include "BrowseProject/General/Items/Utility/WeaponDamage.h"
#include "BrowseProject/General/MeshSockets.h"
#include "ItemData.generated.h"

/// <summary>
/// Перечисление для определения типа предмета, в первую очередь для редактора.
/// Данное перечисление определит, какой тип объекта создастся при генерации внутри игры
/// </summary>
UENUM(BlueprintType)
enum class EEquipmentItemType : uint8
{
	WEAPON = 0 UMETA(DisplayName = "Weapon"),
	ARMOR = 1 UMETA(DisplayName = "Armor"),
	ONESLOT_JEWELERY = 2 UMETA(DisplayName = "Oneslot Jewelery"),
	RING = 3 UMETA(DisplayName = "Ring"),
	DICE = 4 UMETA(DisplayName = "Magic Dice"),
};

/// <summary>
/// Структура аффикса предмета
/// </summary>
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FAffixData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Affix Data"))
	FDataTableRowHandle AffixDataRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Tier"))
	int32 Tier;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FWeaponAppearance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Is Weapon Paired?"))
	bool IsPaired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Static Mesh of RIGHT Hand Weapon"))
	TObjectPtr<UStaticMesh> RightHandWeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Socket Armed of RIGHT Hand Weapon", DisplayAfter = "RightHandWeaponMesh", GetOptions = "WeaponSocketNames.GetSocketOptions"))
	FName RightHandWeaponSocketArmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Socket Hided of RIGHT Hand Weapon", DisplayAfter = "RightHandWeaponSocketArmed", GetOptions = "WeaponSocketNames.GetSocketOptions"))
	FName RightHandWeaponSocketHided;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Static Mesh of LEFT Hand Weapon", EditCondition = "IsDouble == true", EditConditionHides))
	TObjectPtr<UStaticMesh> LeftHandWeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Socket Armed of LEFT Hand Weapon", DisplayAfter = "LeftHandWeaponMesh", EditCondition = "IsDouble == true", EditConditionHides, GetOptions = "WeaponSocketNames.GetSocketOptions"))
	FName LeftHandWeaponSocketArmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Socket Hided of LEFT Hand Weapon", DisplayAfter = "LeftHandWeaponSocketArmed", EditCondition = "IsDouble == true", EditConditionHides, GetOptions = "WeaponSocketNames.GetSocketOptions"))
	FName LeftHandWeaponSocketHided;

};

/// <summary>
/// Базовая структура предметов
/// </summary>
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FItemDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "World Mesh", DisplayPriority = "4"), Category = "Appearance")
	UStaticMesh* WorldMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Set of Icons", DisplayPriority = "5"), Category = "Appearance")
	FIcon IconSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item Name", DisplayPriority = "6"), Category = "Appearance")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item Description", DisplayPriority = "7"), Category = "Appearance")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Rarity", DisplayPriority = "8"), Category = "General Info")
	URarity* Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Stackable", DisplayPriority = "9"), Category = "General Info")
	bool IsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Cost of Item", DisplayPriority = "10"), Category = "General Info")
	int Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item ID", ExposeOnSpawn = "True", DisplayPriority = "1"))
	int ID;
}; 

/// <summary>
/// Структура для всех предметов экипировки
/// Тип предмета определяет, какие поля доступны для редактирования, какие нет
/// </summary>
USTRUCT()
struct BROWSEPROJECT_API FEquipmentDataRow : public FItemDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Type of Item", DisplayPriority = "2"))
	EEquipmentItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "List of Requirements"))
	TMap<EStatKey, int> Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", meta = (DisplayName = "List of Additional Affixes"))
	TArray<FAffixData> Affixes;

	//==========================
	// Свойства предмета, если ItemType == EEquipmentItemType::WEAPON
	//==========================

	// Определяет тип оружия и как оно будет впоследствии одеваться
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Weapon Class", EditCondition = "ItemType == EEquipmentItemType::WEAPON", EditConditionHides))
	EWeaponType WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", meta = (DisplayName = "Weapon Appearance", EditCondition = "ItemType == EEquipmentItemType::WEAPON", EditConditionHides))
	FWeaponAppearance WeaponMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Weapon Damage", EditCondition = "ItemType == EEquipmentItemType::WEAPON", EditConditionHides))
	FWeaponDamage WeaponDamage;

	//==========================
	// Свойства предмета, если ItemType == EEquipmentItemType::ARMOR
	//==========================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Item Slot", ValidEnumValues = "HEAD, BODY, HANDS, LEGS, FEET", 
		EditCondition = "ItemType == EEquipmentItemType::ARMOR", EditConditionHides))
	ESlotType ArmorSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", meta = (DisplayName = "Mesh On Equip", EditCondition = "ItemType == EEquipmentItemType::ARMOR", EditConditionHides))
	USkeletalMesh* ComponentBodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Key of Main Stat", EditCondition = "ItemType == EEquipmentItemType::ARMOR", EditConditionHides))
	EStatKey ArmorKeyStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Stat Value", EditCondition = "ItemType == EEquipmentItemType::ARMOR", EditConditionHides))
	int ArmorValueStat;

	//==========================
	// Свойства предмета, если ItemType == EEquipmentItemType::ONESLOT_JEWELERY
	//==========================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Item Slot", ValidEnumValues = "NECKLACE, WRIST",
		EditCondition = "ItemType == EEquipmentItemType::ONESLOT_JEWELERY", EditConditionHides))
	ESlotType JewelrySlot;

	//==========================
	// Свойства предмета, если ItemType == EEquipmentItemType::RING
	//==========================

	//==========================
	// Свойства предмета, если ItemType == EEquipmentItemType::DICE
	//==========================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Item Slot", ValidEnumValues = "ATTACK_DICE, DAMAGE_DICE, TRIAL_DICE", EditCondition = "ItemType == EEquipmentItemType::DICE", EditConditionHides))
	ESlotType DiceSlot;

	// Index - number of Facet
	// Value - Value on Facet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", meta = (DisplayName = "Array of Value Facets on Dice", EditCondition = "ItemType == EEquipmentItemType::DICE", EditConditionHides))
	TArray<int32> Facets;
};