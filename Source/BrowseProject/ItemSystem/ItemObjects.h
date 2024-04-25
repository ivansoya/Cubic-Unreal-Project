// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "BrowseProject/Character/EquipmentComponent.h"
#include "BrowseProject/Character/InventoryComponent.h"
#include "Roll.h"
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
	/// Функция, которая проверяет подходит ли предмет
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы характеристик</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	bool CheckRequirements(AActor* Character);

	/// <summary>
	/// Экипировка предмета в слот в проверкой статуса слота
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы экипировки</param>
	/// <returns>Возвращает был одет предмет в слот</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool EquipAtSlotCheckStatus(AActor* Character);

	/// <summary>
	/// Снятие предмета с персонажа
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы экипировки</param>
	/// <returns>Возвращает удалось ли снять предмет</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool WithdrawFromCharacter(AActor* Character);

	/// <summary>
	/// Применяет все характеристики предмета к персонажу
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы характеристик</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	virtual bool ApplyAllStatsToCharacter(AActor* Character);

	/// <summary>
	/// Отменяет все характеристики, которые были применены к персонажу с предмета
	/// </summary>
	/// <param name="Character">Класс актера, к которому привязаны интерфейсы характеристик</param>
	/// <returns>Возвращает результат операции</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool AnnulItemStatsFromCharacter(AActor* Character);

	/// <summary>
	/// Константная функция, возвращающая тип слота
	/// </summary>
	/// <returns>Тип слота в формате ESlotType</returns>
	ESlotType GetItemSlot() const;

public:

	// Переопределение добавления предмета в инвентарь
	virtual bool AddToInventory(AActor* Character) override;

	// Переопределение функции считывания данных из структуры
	bool SetDataToObject(FItemDataRow* Data) override;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "List of Item Affixes"))
	TArray<UAffix*> _ItemAffixes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "List of Requirements"))
	TMap<EStatKey, int> _ItemRequirements;

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
	virtual bool EquipAtSlotCheckStatus(AActor* Character) override;

	// Переопределение функции для снятия предмета с персонажа
	virtual bool WithdrawFromCharacter(AActor* Character) override;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Item Slot"))
	ESlotType _Slot;

private:

};

/// <summary>
/// Класс дайсов
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UDice : public UEquipmentItem, public IRoll
{

	GENERATED_BODY()

public:

	// Переопределение функции для одевания предмета на персонажа
	virtual bool EquipAtSlotCheckStatus(AActor* Character) override;

	// Переопределение функции для снятия предмета с персонажа
	virtual bool WithdrawFromCharacter(AActor* Character) override;

	// Функция для считывания данных из структуры
	virtual bool SetDataToObject(FItemDataRow* Data) override;

	// Переопределение функции ролла значений кубика
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 Roll();

private:

	UPROPERTY(VisibleAnywhere, Category = "Dice Stats", meta = (DisplayName = "Map of Facets on Dice"))
	TArray<int32> _Facets;

	UPROPERTY(VisibleAnywhere, Category = "Dice Stats", meta = (DisplayName = "Slot"))
	EDice _Slot;
};

/// <summary>
/// Абстрактный класс для оружия.
/// Наследуемый классы оружия - игровые объекты этого оружия.
/// </summary>
UCLASS(NotBlueprintable, Abstract)
class BROWSEPROJECT_API UWeapon : public UEquipmentItem
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Weapon Mesh"))
	UStaticMesh* WeaponMesh;

public:

	// Функция для считывания данных из структуры
	bool SetDataToObject(FItemDataRow* Data) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Weapon Additional Slot"))
	ESlotType _AdditionalSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Weapon Damage"))
	FWeaponDamage _WeaponDamage;

private:

};

/// <summary>
/// Класс для друручного оружия
/// Обладает дополнительным слотом для надевания.
/// Блокирует второй слот при надевании.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UTwoHanded : public UWeapon
{

	GENERATED_BODY()

public:


protected:


private:

};

/// <summary>
/// Класс для полуторного оружия
/// Обладает дополнительным слотом для надевания.
/// Блокирует второй слот для надевания орудия класса полуторный или двуручный.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API USesquialteral : public UWeapon
{

	GENERATED_BODY()

public:


protected:



private:

};

/// <summary>
/// Класс для одноручного оружия
/// Обладает дополнительным слотом для надевания.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UOneHanded : public UWeapon
{

	GENERATED_BODY()

public:



protected:



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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Item Slot"))
	ESlotType _Slot;

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
