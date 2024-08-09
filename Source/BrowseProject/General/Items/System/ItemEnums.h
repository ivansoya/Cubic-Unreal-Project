// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.generated.h"

/**
 * Перечисление для типов предметов
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	NONE_TYPE = 0 UMETA(DisplayName = "Type for non-used in weapon"),
	SWORD_SHIELD = 1 UMETA(DisplayName = "Sword with Shield"),
	TWOHANDED_SWORD = 2 UMETA(DisplayName = "Twohanded Sword"),
	BASTARD = 3 UMETA(DisplayName = "Bastard"),
	DAGGER_DOUBLE = 4 UMETA(DisplayName = "Daggers"),
	BOW = 5 UMETA(DisplayName = "Bow"),
	STAFF = 6 UMETA(DisplayName = "Staff"),
	MASSIVE_HAMMER = 7 UMETA(DisplayName = "Massive Hammer"),
};

/**
 * Перечисление для типов слотов экипировки
 */
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	NONE_TYPE = 0 UMETA(DisplayName = "NONE"),
	WEAPON = 1 UMETA(DisplayName = "Weapon"),
	HEAD = 2 UMETA(DisplayName = "Head"),
	BODY = 3 UMETA(DisplayName = "Body"),
	HANDS = 4 UMETA(DisplayName = "Hands"),
	LEGS = 5 UMETA(DisplayName = "Legs"),
	FEET = 6 UMETA(DisplayName = "Feet"),
	NECKLACE = 7 UMETA(DisplayName = "Necklace"),
	WRIST = 8 UMETA(DisplayName = "Wrist"),
	FINGER_1 = 9 UMETA(DisplayName = "Finger 1"),
	FINGER_2 = 10 UMETA(DisplayName = "Finger 2"),
	ATTACK_DICE = 11 UMETA(DisplayName = "Attack Dice"),
	DAMAGE_DICE = 12 UMETA(DisplayName = "Damage Dice"),
	TRIAL_DICE = 13 UMETA(DisplayName = "Trial Dice"),
};