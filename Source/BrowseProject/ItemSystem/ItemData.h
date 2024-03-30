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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", Meta = (DisplayName = "Item Slot"))
	ESlotType Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Stats", meta = (DisplayName = "List of Additional Affixes"))
	TArray<UAffix*> Affixes;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FArmorDataRow : public FEquipmentDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor Specials", meta = (DisplayName = "Mesh On Equip"))
	UStaticMesh* ComponentBodyMesh;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Specials", Meta = (DisplayName = "Weapon Additional Slot"))
	ESlotType AdditionalSlot = ESlotType::EST_LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Specials", Meta = (DisplayName = "Weapon Damage"))
	FWeaponDamage WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Specials", Meta = (DisplayName = "Weapon Class"))
	EWeaponType WeaponClass;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FJewelryDataRow : public FEquipmentDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jewelry Specials", Meta = (DisplayName = "Is Ring?"))
	bool IsRing = false;
};