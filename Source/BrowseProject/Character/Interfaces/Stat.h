// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BrowseProject/General/Stats/StatEnums.h"
#include "BrowseProject/General/Element/ElementalDamageType.h"
#include "Stat.generated.h"

// Делегаты для Характеристик
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, const int32, HealthChanged, const int32, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangedSignature, const int32, ManaChanged, const int32, MaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, const int32, StaminaChanged, const int32, MaxStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDurabilityChangedSignature, const int32, DurabilityChanged, const int32, MaxDurability);

// Делегаты событий
// Делегат ролла атаки, вызывается когда персонаж бросает кубики
// AttackRoll - значение грани, которое выпало на кубике, StatKey - ключ характеристики, по которой сравниваются значения у цели с AttackRoll
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorRollAttackDiceSignature, int32&, AttackRoll, EStatKey, StatKey);
// Делегат нанесения урона по цели, вызывается, когда персонаж наносит урон цели
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorDealsDamageToTargetSignature, int32&, AttackRoll, const UElementalDamageType*, DamageType, bool, IsCrit);
// Делегат получения урона, вызывается, когда персонаж получает урон
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorGetHitSignature, int32&, InputDamage, const UElementalDamageType*, DamageType, bool, IsCrit);
// Делегат лечения, вызывается, когда персонаж лечится
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorHealedSignature, int32&, AmountOfHeal);
// Делегат нанесения урона по стойкости, вызывается, когда персонаж не смог пробить броню
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorDealsDurabilityDamageToTargetSignature, int32&, DurabilityDamage);
// Делегат получения урона по стойкости, вызывается, когда персонажу наносят урон по броне
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorTakesDurabilityDamageSignature, int32&, DurabilityDamage);

//Особые события
// Делегат смерти, вызыватся, когда здоровье персонажа падает до нуля
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
// Делегат разрушения защиты у персонажа, вызывается, когда значение стойкости снижается до нуля
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
