// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Перечисление для типов характеристик
 */
UENUM(BlueprintType)
enum class EStatKey : uint8
{
	// Основные типы характеристик
	ESK_Strength = 0 UMETA(DisplayName = "Strength"),
	ESK_Dexterity = 1 UMETA(DisplayName = "Dexterity"),
	ESK_Intelligence = 2 UMETA(DisplayName = "Intelligence"),
	ESK_Durability = 3 UMETA(DisplayName = "Durability"),

	// Критические удары
	ESK_CriticalStrike = 4 UMETA(DisplayName = "Critical Strike Value"),
	ESK_CriticalChance = 5 UMETA(DisplayName = "Critical Strike Chance"),
	
	// Другие дополнительные статы
	ESK_Health = 6 UMETA(DisplayName = "Health"),
	ESK_Mana = 7 UMETA(DisplayName = "Mana"),
	ESK_Endurane = 8 UMETA(DisplayName = "Endurance"),
	ESK_DamageEnduraneBonus = 9 UMETA(DisplayName = "Endurance Damage Bonus"),
	ESK_StabilityPoints = 10 UMETA(DisplayName = "Stability Points"),
	ESK_Defense = 11 UMETA(DisplayName = "Defense"),

	// Скорость
	ESK_AttackSpeed = 12 UMETA(DisplayName = "Auto Attack Speed"),
	ESK_SpellSpeed = 13 UMETA(DisplayName = "Spell Activation Speed"),
	ESK_AbilitySpeed = 14 UMETA(DisplayName = "Ability Speed"),
	ESK_MovementSpeed = 15 UMETA(DisplayName = "Movement Speed"),

	// Баффы к броскам кубика
	ESK_DamageRollBonus = 16 UMETA(DisplayName = "Damage Roll Bonus"),
	ESK_AttackRollBonus = 17 UMETA(DisplayName = "Attack Roll Bonus"),
	ESK_TrialRollBonus = 18 UMETA(DisplayName = "Trial Roll Bonus"),

};
