// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/FIcon.h"
#include "BrowseProject/General/Rarity.h"
#include "Affixes.h"
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
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Rarity"), Category = "Item Stats")
	URarity* Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Stackable"), Category = "Item Stats")
	bool IsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Cost of Item"), Category = "Item Stats")
	int _Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item ID", ExposeOnSpawn = "True"), Category = "Item Stats")
	int _ID;
}; 

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FEquipmentDataRow : public FItemDataRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Main Affix"), Category = "Item Stats")
	UAffix* MainAffix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "List of Additional Affixes"), Category = "Item Stats")
	TArray<UAffix*> Affixes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Tier of Equipment"), Category = "Item Stats")
	int EnchanceLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item Class to Create"), Category = "Item Stats")
	UClass* ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Mesh On Equip"), Category = "Appearance")
	UStaticMesh* ActiveMesh;
};