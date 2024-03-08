// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/FIcon.h"
#include "BrowseProject/General/Rarity.h"
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

	UPROPERTY(EditAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Item Name"));
	FString Name;

	UPROPERTY(EditAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Item Description"));
	FText Description;

	UPROPERTY(EditAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Item Icon Set"));
	FIcon IconSet;

	UPROPERTY(EditAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Item Rarity"));
	URarity* Rarity;

public:

	UFUNCTION(BlueprintCallable)
	virtual void AddToInventory();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Item Stats", Meta = (DisplayName = "Cost"));
	int _Cost;

	UPROPERTY(VisibleAnywhere, Category = "Item Stats", Meta = (DisplayName = "Can be Stacked"));
	bool _IsStackable;

	UPROPERTY(VisibleAnywhere, Category = "Item Stats", Meta = (DisplayName = "Can be Stacked"));
	int _StackedCount;

private:

};


UCLASS(NotBlueprintable, Abstract)
class BROWSEPROJECT_API UEquipment : public UBasicItem
{

	GENERATED_BODY()

public:

	// Модель, которая отображается при одевании предмета
	UPROPERTY(EditAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Item Mesh"));
	UStaticMesh* ActiveMesh;

public:

	// Функция для определения, можно ли надеть предмет на персонажа
	UFUNCTION(BlueprintCallable)
	bool CheckRequirements();

	// Функция для одевания предмета на персонажа
	UFUNCTION(BlueprintCallable)
	virtual void Equip();

protected:

	// Место для списка аффиксов предмета

	// Место для списка требований для предмета

	// Место для списка слотов, в которые можно одеть предмет

private:

};

UCLASS(Blueprintable)
class BROWSEPROJECT_API UOneSlotEquip : public UEquipment
{
	GENERATED_BODY()

public:

	void Equip() override;
};

UCLASS(Blueprintable)
class BROWSEPROJECT_API UMultipleSlotEquip : public UEquipment
{
	GENERATED_BODY()

public:

	void Equip() override;
};

UCLASS(Blueprintable)
class BROWSEPROJECT_API UTwoHandedEquip : public UEquipment
{
	GENERATED_BODY()

public:

	void Equip() override;
};

UCLASS(Blueprintable)
class BROWSEPROJECT_API USesquialteralEquip : public UEquipment
{
	GENERATED_BODY()

public:

	void Equip() override;
};
