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

/**
 * Перечисление статусов слотов экипировки
 */
UENUM(BlueprintType)
enum class ESlotStatus : uint8
{
	BLOCKED = 0 UMETA(DisplayName = "Blocked"),
	DEFAULT = 1 UMETA(DisplayName = "Default"),
	SESQUIALTERAL = 2 UMETA(DisplayName = "Sesquialteral"),
	TWOHANDED = 3 UMETA(DisplayName = "Twohanded"),
};