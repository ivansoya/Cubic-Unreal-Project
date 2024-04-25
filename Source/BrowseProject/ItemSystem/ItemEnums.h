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
	ONEHANDED_SWORD = 0 UMETA(DisplayName = "Onehanded Sword"),
	TWOHANDED_SWORD = 1 UMETA(DisplayName = "Twohanded Sword"),
	BASTARD = 2 UMETA(DisplayName = "Bastard"),
	DAGGER = 3 UMETA(DisplayName = "Dagger"),
	BOW = 4 UMETA(DisplayName = "Bow"),
	STAFF = 5 UMETA(DisplayName = "Staff"),
};

/**
 * Перечисление для типов слотов экипировки
 */
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	LEFT_HAND = 0 UMETA(DisplayName = "Left Hand"),
	RIGHT_HAND = 1 UMETA(DisplayName = "Right Hand"),
	HEAD = 2 UMETA(DisplayName = "Head"),
	BODY = 3 UMETA(DisplayName = "Body"),
	HANDS = 4 UMETA(DisplayName = "Hands"),
	LEGS = 5 UMETA(DisplayName = "Legs"),
	FEET = 6 UMETA(DisplayName = "Feet"),
	NECKLACE = 7 UMETA(DisplayName = "Necklace"),
	WRIST = 8 UMETA(DisplayName = "Wrist"),
	FINGER_1 = 9 UMETA(DisplayName = "Finger 1"),
	FINGER_2 = 10 UMETA(DisplayName = "Finger 2"),
};

UENUM(BlueprintType)
enum class EDice : uint8
{
	ATTACK_DICE = 0 UMETA(DisplayName = "Attack Dice"),
	DAMAGE_DICE = 1 UMETA(DisplayName = "Damage Dice"),
	TRIAL_DICE = 2 UMETA(DisplayName = "Trial Dice"),
};

/**
 * Перечисление статусов слотов экипировки
 */
UENUM(BlueprintType)
enum class ESlotStatus : uint8
{
	NOT_EXISTING = 0 UMETA(DisplayName = "Not Existing"),
	BLOCKED = 1 UMETA(DisplayName = "Blocked"),
	DEFAULT = 2 UMETA(DisplayName = "Default"),
	SESQUIALTERAL = 3 UMETA(DisplayName = "Sesquialteral"),
	TWOHANDED = 4 UMETA(DisplayName = "Twohanded"),
};