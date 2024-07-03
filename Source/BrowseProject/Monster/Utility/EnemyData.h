// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Stats/StatEnums.h"
#include "BrowseProject/Monster/Utility/FMonsterDamage.h"
#include "EnemyData.generated.h"

/// <summary>
/// Enumeration that defines the type of monster
/// RESISTANCE - сопротивление элементальному урону
/// DAMAGE_BONUS - элементальный урон
/// </summary>
UENUM()
enum class EMonsterClass : uint8
{
	WEAK = 0 UMETA(DisplayName = "Weak"),
	COMMON = 1 UMETA(DisplayName = "Common"),
	STRONG = 2 UMETA(DisplayName = "Strong"),
	ELITE = 3 UMETA(DisplayName = "Elite"),
	BOSS = 4 UMETA(DisplayName = "Boss"),
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FMonsterStatPair 
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Stat Key"))
	EStatKey Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Stat Value"))
	int32 Value;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FMonsterResistancePair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Resistance Type"))
	UElementalDamageType* Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Resistance Value"))
	int32 Value;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (DisplayName = "Monster Name"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info", meta = (DisplayName = "Monster Class"))
	EMonsterClass Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (DisplayName = "Monster Health"))
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (DisplayName = "Monster Regen Health"))
	int32 HealthRegeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense", meta = (DisplayName = "Monster Defense"))
	int32 Defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability", meta = (DisplayName = "Monster Durability"))
	int32 Durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability", meta = (DisplayName = "Monster Durability Regeneration per second"))
	int32 RegenDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durability", meta = (DisplayName = "Monster Start Durability Regeneration, at seconds after Durability gone"))
	int32 StartRegenDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (DisplayName = "Monster Damage"))
	FMonsterDamage Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize, Category = "Monster Stats", meta = (DisplayName = "Monster Stats"))
	TArray<FMonsterStatPair> StatList = { 
		FMonsterStatPair(EStatKey::STRENGTH, 0),
		FMonsterStatPair(EStatKey::DEXTERITY, 0),
		FMonsterStatPair(EStatKey::INTELLIGENCE, 0),
		FMonsterStatPair(EStatKey::ENDURANCE, 0),
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Resistances", meta = (DisplayName = "Monster Resistances"))
	TArray<FMonsterResistancePair> ResistanceList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience", meta = (DisplayName = "Monster Level"))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience", meta = (DisplayName = "Monster Exp gained"))
	int32 ExpGained;

}; 
