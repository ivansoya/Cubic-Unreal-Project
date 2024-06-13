// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/// <summary>
/// Перечисление, которое определеяет тип элементальной характеристики
/// RESISTANCE - сопротивление элементальному урону
/// DAMAGE_BONUS - элементальный урон
/// </summary>
UENUM()
enum class EStatElementalType: uint8
{
	RESISTANCE = 0 UMETA(DisplayName = "Elemental Resistance"),
	DAMAGE_BONUS = 1 UMETA(DisplayName = "Elemental Damage"),
};

/// <summary>
/// Перечисление, которое определеяет тип возвращаемого значения характерстики
/// BASE - возвращение базового показателя (врожденного)
/// ADDED - возвращение показателя, который был получен из экипировок, умений и пассивок
/// GENERAL - сумма BASE и GENERAL
/// </summary>
UENUM()
enum class EStatTypeRetuned : uint8
{
	GENERAL = 0 UMETA(DisplayName = "General Value"),
	BASE = 1 UMETA(DisplayName = "Base Value"),
	ADDED = 2 UMETA(DisplayName = "Added Value"),
};

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
	ENDURANCE = 3 UMETA(DisplayName = "Endurance"),
	
	// Другие дополнительные статы
	HEALTH = 4 UMETA(DisplayName = "Health"),
	MANA = 5 UMETA(DisplayName = "Mana"),
	STAMINA = 6 UMETA(DisplayName = "Stamina"),
	DURABILITY = 7 UMETA(DisplayName = "Durability"),
	DURABILITY_DAMAGE_BONUS = 8 UMETA(DisplayName = "Durability Damage Bonus"),
	DEFENCE = 9 UMETA(DisplayName = "Defence"),

	// Критические удары
	CRITICAL_STRIKE = 10 UMETA(DisplayName = "Critical Strike Value"),
	CRITICAL_CHANCE = 11 UMETA(DisplayName = "Critical Strike Chance"),

	// Скорость
	ATTACK_SPEED = 12 UMETA(DisplayName = "Attack Speed"),
	SPELL_SPEED = 13 UMETA(DisplayName = "Spell Activation Speed"),
	ABILITY_SPEED = 14 UMETA(DisplayName = "Ability Speed"),
	MOVEMENT_SPEED = 15 UMETA(DisplayName = "Movement Speed"),

	// Баффы к броскам кубика
	DAMAGE_ROLL_BONUS = 16 UMETA(DisplayName = "Damage Roll Bonus"),
	ATTACK_ROLL_BONUS = 17 UMETA(DisplayName = "Attack Roll Bonus"),
	TRIAL_ROLL_BONUS = 18 UMETA(DisplayName = "Trial Roll Bonus"),

};
