// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BrowseProject/General/Stats/StatEnums.h"
#include "BrowseProject/General/Element/ElementalDamageType.h"
#include "Stat.generated.h"

// �������� ��� �������������
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, const int32, HealthChanged, const int32, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangedSignature, const int32, ManaChanged, const int32, MaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, const int32, StaminaChanged, const int32, MaxStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDurabilityChangedSignature, const int32, DurabilityChanged, const int32, MaxDurability);

// �������� �������
// ������� ����� �����, ���������� ����� �������� ������� ������
// AttackRoll - �������� �����, ������� ������ �� ������, StatKey - ���� ��������������, �� ������� ������������ �������� � ���� � AttackRoll
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorRollAttackDiceSignature, int32&, AttackRoll, EStatKey, StatKey);
// ������� ��������� ����� �� ����, ����������, ����� �������� ������� ���� ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorDealsDamageToTargetSignature, int32&, AttackRoll, const UElementalDamageType*, DamageType, bool, IsCrit);
// ������� ��������� �����, ����������, ����� �������� �������� ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorGetHitSignature, int32&, InputDamage, const UElementalDamageType*, DamageType, bool, IsCrit);
// ������� �������, ����������, ����� �������� �������
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorHealedSignature, int32&, AmountOfHeal);
// ������� ��������� ����� �� ���������, ����������, ����� �������� �� ���� ������� �����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorDealsDurabilityDamageToTargetSignature, int32&, DurabilityDamage);
// ������� ��������� ����� �� ���������, ����������, ����� ��������� ������� ���� �� �����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorTakesDurabilityDamageSignature, int32&, DurabilityDamage);

//������ �������
// ������� ������, ���������, ����� �������� ��������� ������ �� ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
// ������� ���������� ������ � ���������, ����������, ����� �������� ��������� ��������� �� ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBreakDefenceSignature);


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BROWSEPROJECT_API IStatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	int32 RollAttackToEnemy(AActor* Target, const UElementalDamageType* DamageType);

	UFUNCTION(BlueprintNativeEvent)
	int32 DealDamageToTarget(AActor* Target, const UElementalDamageType* DamageType);

	UFUNCTION(BlueprintNativeEvent)
	int32 TakeDamageFromEnemy(int32 Damage, const UElementalDamageType* DamageType, bool IsCrit);

	UFUNCTION(BlueprintNativeEvent)
	int32 TakeHeal(int32 HealAmount);

	UFUNCTION(BlueprintNativeEvent)
	void ChangeCharacterStatValue(int32 Value, EStatKey Key, EStatTypeRetuned Type);

	UFUNCTION(BlueprintNativeEvent)
	void ChangeElementalValue(int32 Value, UElementalDamageType* Element, EStatElementalType Type);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetCharacterLevel();

	UFUNCTION(BlueprintNativeEvent)
	FString GetCharacterName();

	UFUNCTION(BlueprintNativeEvent)
	void GetCharacterHealth(int32& CurrentHealth, int32& MaxHealth);

	UFUNCTION(BlueprintNativeEvent)
	void GetCharacterDurability(int32& CurrentDurability, int32& MaxDurability);

};
