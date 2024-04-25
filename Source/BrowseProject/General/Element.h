// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Element.generated.h"

/**
 * Класс типизации элементального урона
 */
UCLASS()
class BROWSEPROJECT_API UElementalDamageType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Name"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Text Color"))
	FColor TextColor;

	// Место для эффекта, который накладывается при нанесении урона
};

/**
 * Структура для определения урона оружием
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

UCLASS()
class BROWSEPROJECT_API UElementalSystem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Elemental Damage")
	static void SetEffectOnTarget();
};


