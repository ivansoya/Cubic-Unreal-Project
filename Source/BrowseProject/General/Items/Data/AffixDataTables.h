// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Stats/StatEnums.h"
#include "BrowseProject/General/Element/ElementalDamageType.h"
#include "AffixDataTables.generated.h"


USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FBaseParameter
{
	GENERATED_BODY()

	// Значение, на которое будет увеличиваться значение аффикса при повышении уровня параметра
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Tier Step Value", DisplayPriority = "2"))
	int32 TierStep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Is Random", DisplayPriority = "3"))
	bool IsRandom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Constant Value of Parameter", EditCondition = "IsRandom == false", DisplayPriority = "4"))
	int32 ConstantValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Min Value of Parameter", EditCondition = "IsRandom == true", DisplayPriority = "5"))
	int32 MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Max Value of Parameter", EditCondition = "IsRandom == true", DisplayPriority = "6"))
	int32 MaxValue;

};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FStatParameter : public FBaseParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Key of Parameter", DisplayPriority = "1"))
	EStatKey Key;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FElementParameter : public FBaseParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Type of Element", EditCondition = "IsAllElements == false", DisplayPriority = "1"))
	UElementalDamageType* Element;
};


/// <summary>
/// Структура для аффикса, предоставляющего напрямую характеристики персонажа
/// Аффикс может иметь разное количество бонусов, которое регулируется дизайнером
/// </summary>
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FStatAffixDataRow : public FTableRowBase
{
	GENERATED_BODY()

	// Предоставляет описание данного аффикса
	// Параметры из списка обычных параметров указываются как %[индекс массива Parameters]
	// Параметры из списка элементального урона указываются как #[индекс массива ElementalDamages]
	// Параметры из списка элементального сопротивления указываются как &[индекс массива ElementalResistances]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Description"));
	FText Description;

	// Количество уровней у аффикса
	// Чем выше уровень - тем хуже значения, таким образом 1 тир - всегда является самым лучшим у аффиксов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Number of Tiers"));
	int32 TierNum;

	// Список обычных параметров, которые предоставляют аффиксы
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "List of Parameters"))
	TArray<FStatParameter> Parameters;

	// Список бонусов к элементальному урону
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "List of Elemental Damage Types Bonuses"))
	TArray<FElementParameter> ElementalDamages;

	// Список сопротивлений урону
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "List of Elemental Resistances Values"))
	TArray<FElementParameter> ElementalResistances;

};