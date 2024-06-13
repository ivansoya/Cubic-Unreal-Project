// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Stats/StatEnums.h"
#include "BrowseProject/Monster/Utility/FMonsterDamage.h"
#include "EnemyData.generated.h"

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FMonsterStatPair 
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Stat Key"))
	EStatKey Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Stat Value"))
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Monster Health"))
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Monster Defence"))
	int32 Defence;

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

}; 
