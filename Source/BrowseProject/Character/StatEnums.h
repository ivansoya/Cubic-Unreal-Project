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
	STRENGTH = 0 UMETA(DisplayName = "Strength"),
	DEXTERITY = 1 UMETA(DisplayName = "Dexterity"),
	INTELLIGENCE = 2 UMETA(DisplayName = "Intelligence"),
	DURABILITY = 3 UMETA(DisplayName = "Durability"),

	// Критические удары
	CRITICAL_STRIKE = 4 UMETA(DisplayName = "Critical Strike Value"),
	CRITICAL_CHANCE = 5 UMETA(DisplayName = "Critical Strike Chance"),
	
	// Другие дополнительные статы
	HEALTH = 6 UMETA(DisplayName = "Health"),
	MANA = 7 UMETA(DisplayName = "Mana"),
	ENDURANCE = 8 UMETA(DisplayName = "Endurance"),
	DAMAGE_ENDURANCE_BONUS = 9 UMETA(DisplayName = "Endurance Damage Bonus"),
	STABILITY_POINTS = 10 UMETA(DisplayName = "Stability Points"),
	DEFENSE = 11 UMETA(DisplayName = "Defense"),

	// Скорость
	ATTACK_SPEED = 12 UMETA(DisplayName = "Auto Attack Speed"),
	SPELL_SPEED = 13 UMETA(DisplayName = "Spell Activation Speed"),
	ABILITY_SPEED = 14 UMETA(DisplayName = "Ability Speed"),
	MOVEMENT_SPEED = 15 UMETA(DisplayName = "Movement Speed"),

	// Баффы к броскам кубика
	DAMAGE_ROLL_SPEED = 16 UMETA(DisplayName = "Damage Roll Bonus"),
	ATTACK_ROLL_BONUS = 17 UMETA(DisplayName = "Attack Roll Bonus"),
	TRIAL_ROLL_BONUS = 18 UMETA(DisplayName = "Trial Roll Bonus"),

};
