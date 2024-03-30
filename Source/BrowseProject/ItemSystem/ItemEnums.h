// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEnums.generated.h"

/**
 * ������������ ��� ����� ���������
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_OnehandedSword = 0 UMETA(DisplayName = "Onehanded Sword"),
	EWT_TwohandedSword = 1 UMETA(DisplayName = "Twohanded Sword"),
	EWT_Bastard = 2 UMETA(DisplayName = "Bastard"),
	EWT_Dagger = 3 UMETA(DisplayName = "Dagger"),
	EWT_Bow = 4 UMETA(DisplayName = "Bow"),
	EWT_Staff = 5 UMETA(DisplayName = "Staff"),
};

/**
 * ������������ ��� ����� ������ ����������
 */
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	EST_LeftHand = 0 UMETA(DisplayName = "Left Hand"),
	EST_RightHand = 1 UMETA(DisplayName = "Right Hand"),
	EST_Head = 2 UMETA(DisplayName = "Head"),
	EST_Body = 3 UMETA(DisplayName = "Body"),
	EST_Hands = 4 UMETA(DisplayName = "Hands"),
	EST_Legs = 5 UMETA(DisplayName = "Legs"),
	EST_Feet = 6 UMETA(DisplayName = "Feet"),
	EST_Necklace = 7 UMETA(DisplayName = "Necklace"),
	EST_Wrist = 8 UMETA(DisplayName = "Wrist"),
	EST_Finger_1 = 9 UMETA(DisplayName = "Finger 1"),
	EST_Finger_2 = 10 UMETA(DisplayName = "Finger 2"),
};