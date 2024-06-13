// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDamage.generated.h"

/**
 * —труктура дл€ определени€ урона оружием
 */
USTRUCT(BlueprintType)
struct FWeaponDamage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Elemental Damage Type"))
	UElementalDamageType* DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Minimal Additional Damage to Roll"))
	int MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Maximum Additional Damage to Roll"))
	int MaxDamage;
};