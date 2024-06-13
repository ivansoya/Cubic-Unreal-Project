// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Items/Data/AffixDataTables.h"
#include "Affixes.generated.h"

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FStatPair
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Stat Key"))
	EStatKey Key;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Value"))
	int32 Value;
};

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FElementPair
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Damage Type"))
	UElementalDamageType* DamageType;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Value"))
	int32 Value;
};

UINTERFACE(MinimalAPI)
class UAffix : public UInterface
{
	GENERATED_BODY()
};

/**
 * Интерфейс, Определяющий функции аффиксов
 */
class BROWSEPROJECT_API IAffix
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void Apply(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent)
	void Cancel(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent)
	FText GetText();

};

/**
 * Основной вид аффиксов в игре
 * Данный аффикс дает фиксированный бонус к характеристике персонажу
 * Класс содержит данные о типе характеристики, которая есть у персонажа и ее значение.
 */
UCLASS()
class BROWSEPROJECT_API UStatAffix : public UObject, public IAffix
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void Apply(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent)
	void Cancel(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent)
	FText GetText();

	//UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Affix")
	void SetParams(TArray<FStatPair> StatList,
		TArray<FElementPair> ElementalDamageList,
		TArray<FElementPair> ElementalResistanceList,
		int32 TierNum, int32 Tier, FText Description);

private:
	
	/// <summary>
	/// Вспомогательная функция для изменения характеристик
	/// </summary>
	void ChangeCharacterStatValues(AActor* Actor, bool IsPositive);

private:

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "List of Character Stats"))
	TArray<FStatPair> _StatList;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "List of Bonuses to Elemental Damage"))
	TArray<FElementPair> _ElementalDamageList;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "List of Bonuses to Elemental Resistances"))
	TArray<FElementPair> _ElementalResistanceList;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Description"))
	FText _Description;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Tier of Affix"))
	int32 _Tier;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Number of Tiers"))
	int32 _NumberOfTiers;
};


UCLASS()
class BROWSEPROJECT_API UItemDataFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintCallable, Category = "Item Data Function Library")
	template<typename T>
	static T* FindDataRowAfterCast(TObjectPtr<const UDataTable> DataTable, FName RowName);
	
	/// <summary>
	/// Функция, которая инициализирует аффикс характеристик из соответствующей структуры в таблице данных
	/// </summary>
	//UFUNCTION(BlueprintCallable, Category = "Dice Project|Item Data")
	static UObject* SpawnAffixFromTableRow(TObjectPtr<const UDataTable> DataTable, FName RowName, int32 Tier);

	/// <summary>
	/// Вспомогательная функция для получения пары значений
	/// </summary>
	/// <returns></returns>
	static FElementPair GetElementalPair(const FElementParameter Parameter, int32 MaxTier, int32 Tier);
};
