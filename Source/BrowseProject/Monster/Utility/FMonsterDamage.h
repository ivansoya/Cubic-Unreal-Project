// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Element/ElementalDamageType.h"
#include "FMonsterDamage.generated.h"

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FMonsterDamageMinMax
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Minimum Damage"))
	int32 Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Maximum Damage"))
	int32 Max;
};

/**
 * Структура урона монстра, предоставляет значения урона для обычных атак монстра
 */
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FMonsterDamage
{
	GENERATED_BODY()

	// Рол атаки у монстров всегда одинаковый
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Attack Roll of Monster"))
	int32 AttackRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Type of Elemental Damage"))
	UElementalDamageType* DamageType;

	// Список урона по атакам монстрам, количество таких значений должно быть равно количеству атак
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Attack Damage of Monster"))
	TArray<FMonsterDamageMinMax> AttackDamageList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Critical Damage"))
	int32 CriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Critical Chance"))
	int32 CriticalChance;
};
