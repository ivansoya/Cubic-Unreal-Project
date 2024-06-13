// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Stats/StatEnums.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

#define MAXIMUM_RESISTANCE_DEFAULT 75

class UElementalDamageType;

/**
* Структура для значений статов 
*/
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FStatValues
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Base Value of Stat"))
	int32 Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Added Value of Stat"))
	int32 AddedValue;
};

/**
* Структура для значений сопротивлений
*/
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FResistanceValue 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Current Value"))
	int32 Current;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Maximum Value of Resistance"))
	int32 MaxValue = MAXIMUM_RESISTANCE_DEFAULT;
};

UCLASS(Blueprintable)
class BROWSEPROJECT_API UDefaultStatsCharacter : public UDataAsset
{
	GENERATED_BODY()

public:

	// Список со значениями характеристик
	UPROPERTY(EditAnywhere, Category = "Stat Lists", meta = (DisplayName = "Sub Stat List"))
	TMap<EStatKey, int32> StatList;

	// Список со значениями по типам сопротивлений урону
	UPROPERTY(EditAnywhere, Category = "Stat Lists", meta = (DisplayName = "Elemental Resistance"))
	TMap<UElementalDamageType*, FResistanceValue> Resistances;

	// Список со значениями дополнительного стихийного урона
	UPROPERTY(EditAnywhere, Category = "Stat Lists", meta = (DisplayName = "Extra Elemental Damage"))
	TMap<UElementalDamageType*, int32> ExtraElementalDamage;

};

/**
 * Класс-компонент для персонажа.
 * Выступает в роли контейнера для хранения и манипулирования с характеристиками персонажа.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BROWSEPROJECT_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UStatComponent();

protected:

	virtual void BeginPlay() override;

	virtual void OnComponentCreated() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Lists", meta = (DisplayName = "Default Stats"))
	UDefaultStatsCharacter* _DefaultStats;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Добавляет значение к характеристике их списка
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	void AddStatValue(EStatKey Stat, int32 Value, EStatTypeRetuned AddTo = EStatTypeRetuned::ADDED);

	/// <summary>
    /// Добавляет значение к характеристике их списка
    /// </summary>
	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	int32 GetStatValue(EStatKey Stat, EStatTypeRetuned StatType) const;

	/// <summary>
	/// Добавляет значения сопротивления к соответствующему элементу
	/// </summary>
	/// <param name="Elemental">Тип Элемента</param>
	/// <param name="Value">Значение</param>
	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	void AddElementalResistanceValue(UElementalDamageType* Elemental, int32 Value);

	/// <summary>
	/// Добавляет значения максимальное сопротивление к соответствующему элементу
	/// </summary>
	/// <param name="Elemental">Тип Элемента</param>
	/// <param name="Value">Значение</param>
	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	void AddMaximumElementalResistanceValue(UElementalDamageType* Elemental, int32 Value);

	/// <summary>
	/// Возвращает значение сопротивления элементу
	/// </summary>
	/// <param name="Elemental">Тип Элемента</param>
	/// <returns>Значение сопротивления</returns>
	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	int32 GetElementalResistanceValue(UElementalDamageType* Elemental) const;

	/// <summary>
	/// Добавляет значения урона к соответствующему элементу
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	void AddExtraElementalDamage(UElementalDamageType* Elemental, int32 Value);

	/// <summary>
	/// Возвращает значение добавочного элементального урона
	/// </summary>
	/// <param name="Elemental">Элемент</param>
	/// <returns>Значение добавочного урона</returns>
	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	int32 GetElementalExtraDamage(UElementalDamageType* Elemental) const;

	// Стандартные геттеры
	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	TMap<EStatKey, FStatValues> GetCharacterStats() const;

	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	TMap<UElementalDamageType*, FResistanceValue> GetElementalResistance() const;

	UFUNCTION(BlueprintCallable, Category = "Dice Project|Stat Component")
	TMap<UElementalDamageType*, int32> GetExtraElementalDamage() const;

private:
	// Перечень списков характеристик

	// Список со статами персонажа
	UPROPERTY(VisibleAnywhere, Category = "Stat Lists", meta = (DisplayName = "Sub Stat List"))
	TMap<EStatKey, FStatValues> _Stats;

	// Список со значениями по типам сопротивлений урону
	UPROPERTY(VisibleAnywhere, Category = "Stat Lists", meta = (DisplayName = "Elemental Resistance"))
	TMap<UElementalDamageType*, FResistanceValue> _Resistances;

	// Список со значениями дополнительного стихийного урона
	UPROPERTY(VisibleAnywhere, Category = "Stat Lists", meta = (DisplayName = "Extra Elemental Damage"))
	TMap<UElementalDamageType*, int32> _ExtraElementalDamage;
};
