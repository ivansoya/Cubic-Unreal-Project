// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Items/Data/ItemData.h"
#include "BrowseProject/Character/Components/EquipmentComponent.h"
#include "BrowseProject/Character/Components/InventoryComponent.h"
#include "BrowseProject/General/Items/Interface/Roll.h"
#include "ItemObjects.generated.h"


/**
 * Класс, который используется для объектов предметов, с которыми можно взаимодействовать.
 * Манипулирование предметами осуществляется через интерфейс, данные классы не могут иметь игровую модель.
 */
UCLASS(Blueprintable)
class BROWSEPROJECT_API UBasicItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Appearance", Meta = (DisplayName = "Item Name"));
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Appearance", Meta = (DisplayName = "Item Description"));
	FText Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Appearance", Meta = (DisplayName = "Item Icon Set"));
	FIcon IconSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Appearance", Meta = (DisplayName = "Item Rarity"));
	URarity* Rarity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Appearance", Meta = (DisplayName = "World Mesh of Item"));
	UStaticMesh* WorldMesh;

public:

	/// <summary>
	/// Функция добавления предмета в инвентарь
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы инвентаря</param>
	/// <returns>Возвращает был ли добавлен предмет</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool AddToInventory(AActor* Character);

	/// <summary>
	/// Функция, которая считывает все данные из предоставленной структуры
	/// </summary>
	/// <param name="Data">Структура данных</param>
	/// <returns>Результат операции</returns>
	virtual bool SetDataToObject(FItemDataRow* Data);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Cost"));
	int _Cost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Can be Stacked"));
	bool _IsStackable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Count of Stacked Item", EditCondition = "_IsStackable == true"));
	int _StackedCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Item ID"));
	int _ID;

private:

};


UCLASS(NotBlueprintable, Abstract)
class BROWSEPROJECT_API UEquipmentItem : public UBasicItem
{

	GENERATED_BODY()

public: 

	/// <summary>
	/// Экипировка предмета в слот в проверкой статуса слота
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы экипировки</param>
	/// <returns>Возвращает был одет предмет в слот</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool EquipAtCharacterSlot(AActor* Character) const;

	/// <summary>
	/// Снятие предмета с персонажа
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы экипировки</param>
	/// <returns>Возвращает удалось ли снять предмет</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool WithdrawFromCharacterSlot(AActor* Character) const;

	/// <summary>
	/// Применяет все характеристики предмета к персонажу
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы характеристик</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	virtual bool ApplyAllStatsToCharacter(AActor* Character) const;

	/// <summary>
	/// Отменяет все характеристики, которые были применены к персонажу с предмета
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы характеристик</param>
	/// <returns>Возвращает результат операции</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool AnnulItemStatsFromCharacter(AActor* Character) const;

	/// <summary>
	/// Константная функция, возвращающая тип слота
	/// </summary>
	/// <returns>Тип слота в формате ESlotType</returns>
	/// UFUNCTION(BlueprintCallable)
	virtual ESlotType GetItemSlot() const;

public:

	// Переопределение добавления предмета в инвентарь
	virtual bool AddToInventory(AActor* Character) override;

	// Переопределение функции считывания данных из структуры
	bool SetDataToObject(FItemDataRow* Data) override;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "List of Item Affixes"))
	TArray<UObject*> _ItemAffixes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "List of Requirements"))
	TMap<EStatKey, int> _ItemRequirements;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Item Slot"))
	ESlotType _Slot;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Item Data Row"))
	const FEquipmentDataRow* _ItemData;

private:

};

/// <summary>
/// Класс для брони
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UArmor : public UEquipmentItem
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Body Mesh"))
	USkeletalMesh* ComponentBodyMesh;

public:

	// Переопределение функции для одевания предмета на персонажа
	virtual bool EquipAtCharacterSlot(AActor* Character) const override;

	// Переопределение функции для снятия предмета с персонажа
	virtual bool WithdrawFromCharacterSlot(AActor* Character) const override;

	// Переопределение функции применение характеристик к персонажу
	//virtual bool ApplyAllStatsToCharacter(AActor* Character) override;

	// Переопределение функции отмены примененных характеристик у персонажа
	//virtual bool AnnulItemStatsFromCharacter(AActor* Character) override;

	// Функция для считывания данных из структуры
	virtual bool SetDataToObject(FItemDataRow* Data) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Main Stat"))
	EStatKey _ArmorKeyStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Stat Value"))
	int _ArmorValueStat;

private:

};

/// <summary>
/// Класс дайсов
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UDice : public UEquipmentItem
{

	GENERATED_BODY()

public:

	// Переопределение функции для одевания предмета на персонажа
	virtual bool EquipAtCharacterSlot(AActor* Character) const override;

	// Переопределение функции для снятия предмета с персонажа
	virtual bool WithdrawFromCharacterSlot(AActor* Character) const override;

	// Функция для считывания данных из структуры
	virtual bool SetDataToObject(FItemDataRow* Data) override;

	// Переопределение функции ролла значений кубика
	UFUNCTION(BlueprintCallable)
	int32 Roll() const;

private:

	UPROPERTY(VisibleAnywhere, Category = "Dice Stats", meta = (DisplayName = "Map of Facets on Dice"))
	TArray<int32> _Facets;
};

/// <summary>
/// Абстрактный класс для оружия.
/// Наследуемый классы оружия - игровые объекты этого оружия.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UWeapon : public UEquipmentItem
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Weapon Appearance"))
	FWeaponAppearance WeaponAppearance;

public:

	// Функция для считывания данных из структуры
	bool SetDataToObject(FItemDataRow* Data) override;

	// Переопределение функции для одевания предмета на персонажа
	virtual bool EquipAtCharacterSlot(AActor* Character) const override;

	// Переопределение функции для снятия предмета с персонажа
	virtual bool WithdrawFromCharacterSlot(AActor* Character) const override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Weapon Damage"))
	FWeaponDamage _WeaponDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Weapon Class"))
	EWeaponType _WeaponClass;

private:

};

/// <summary>
/// Класс для бижутерии.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UJewelry : public UEquipmentItem
{

	GENERATED_BODY()

public:

protected:

private:

};

/// <summary>
/// Класс для колец.
/// Кольца имеют дополнительный слот для надевания.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API URing : public UEquipmentItem
{

	GENERATED_BODY()

public:


protected:


private:

};
