// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.h"
#include "Affixes.h"
#include "BrowseProject/General/FIcon.h"
#include "BrowseProject/General/Rarity.h"
#include "BrowseProject/General/Element.h"
#include "BrowseProject/Character/StatEnums.h"
#include "ItemData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FItemDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "World Mesh"), Category = "Appearance")
	UStaticMesh* WorldMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Set of Icons"), Category = "Appearance")
	FIcon IconSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item Name"), Category = "Appearance")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item Description"), Category = "Appearance")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Rarity"), Category = "Item Stats")
	URarity* Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Stackable"), Category = "Item Stats")
	bool IsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Cost of Item"), Category = "Item Stats")
	int Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item ID", ExposeOnSpawn = "True"), Category = "Item Stats")
	int ID;
}; 

// For not use in blueprints
USTRUCT()
struct BROWSEPROJECT_API FEquipmentDataRow : public FItemDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "List of Requirements"))
	TMap<EStatKey, int> Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", meta = (DisplayName = "List of Additional Affixes"))
	TArray<UAffix*> Affixes;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FDiceDataRow : public FEquipmentDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Item Slot"))
	EDice DiceSlot;

	// Index - number of Facet
	// Value - Value on Facet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dice Stats", meta = (DisplayName = "Array of Value Facets on Dice"))
	TArray<int32> Facets;
};

UENUM(Meta = (Bitglags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EArmorSlots
{
	EAC_Head = ESlotType::HEAD UMETA(DisplayName = "Head"),
	EAC_Body = ESlotType::BODY UMETA(DisplayName = "Body"),
	EAC_Hands = ESlotType::HANDS UMETA(DisplayName = "Hands"),
	EAC_Legs = ESlotType::LEGS UMETA(DisplayName = "Legs"),
	EAC_Feet = ESlotType::FEET UMETA(DisplayName = "Feet"),
};
ENUM_CLASS_FLAGS(EArmorSlots);

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FArmorDataRow : public FEquipmentDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Item Slot", Bitmask, BitmaskEnum = "EArmorSlots"))
	ESlotType ArmorSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor Specials", meta = (DisplayName = "Mesh On Equip"))
	USkeletalMesh* ComponentBodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor Specials", Meta = (DisplayName = "Key of Main Stat"))
	EStatKey ArmorKeyStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor Specials", Meta = (DisplayName = "Stat Value"))
	int ArmorValueStat;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FWeaponDataRow : public FEquipmentDataRow
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Specials", Meta = (DisplayName = "Weapon Mesh"))
	UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Specials", Meta = (DisplayName = "Weapon Damage"))
	FWeaponDamage WeaponDamage;

	// Определяет тип оружия и как оно будет впоследствии одеваться
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Specials", Meta = (DisplayName = "Weapon Class"))
	EWeaponType WeaponClass;
};

UENUM(Meta = (Bitglags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EJewelrySlots
{
	EJC_Necklace = ESlotType::NECKLACE UMETA(DisplayName = "Necklace"),
	EJC_Wrist = ESlotType::WRIST UMETA(DisplayName = "Wrist"),
};
ENUM_CLASS_FLAGS(EJewelrySlots);

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FJewelryDataRow : public FEquipmentDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Item Slot", Bitmask, BitmaskEnum = "EJewelrySlots"))
	ESlotType JewelrySlot;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FRingDataRow : public FEquipmentDataRow
{
	GENERATED_BODY()
};