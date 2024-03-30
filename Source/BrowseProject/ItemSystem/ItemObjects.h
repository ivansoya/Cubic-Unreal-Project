// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "ItemObjects.generated.h"

/**
 * �����, ������� ������������ ��� �������� ���������, � �������� ����� �����������������.
 * ��������������� ���������� �������������� ����� ���������, ������ ������ �� ����� ����� ������� ������.
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

	UPROPERTY(EditAnywhere, Category = "Item Appearance", Meta = (DisplayName = "World Mesh of Item"));
	UStaticMesh* WorldMesh;

public:

	UFUNCTION(BlueprintCallable)
	virtual void AddToInventory();

	// ������� ��� ���������� ������ �� ���������
	virtual bool SetDataToObject(FItemDataRow* Data);

protected:

	UPROPERTY(VisibleAnywhere, Category = "Item Stats", Meta = (DisplayName = "Cost"));
	int _Cost;

	UPROPERTY(VisibleAnywhere, Category = "Item Stats", Meta = (DisplayName = "Can be Stacked"));
	bool _IsStackable;

	UPROPERTY(VisibleAnywhere, Category = "Item Stats", Meta = (DisplayName = "Count of Stacked Item", EditCondition = "_IsStackable == true"));
	int _StackedCount;

	UPROPERTY(VisibleAnywhere, Category = "Item Stats", Meta = (DisplayName = "Item ID"));
	int _ID;

private:

};


UCLASS(NotBlueprintable, Abstract)
class BROWSEPROJECT_API UEquipment : public UBasicItem
{

	GENERATED_BODY()

public:

	// ������� ��� �����������, ����� �� ������ ������� �� ���������
	UFUNCTION(BlueprintCallable)
	bool CheckRequirements();

	// ������� ��� �������� �������� �� ���������
	UFUNCTION(BlueprintCallable)
	virtual void Equip();

	// ������� ��� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "List of Item Affixes"))
	TArray<UAffix*> _ItemAffixes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "List of Requirements"))
	TMap<EStatKey, int> _ItemRequirements;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Item Slot"))
	ESlotType _Slot;

private:

};

/// <summary>
/// ����� ��� �����
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UArmor : public UEquipment
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Body Mesh"))
	UStaticMesh* ComponentBodyMesh;

public:

	// ������� ��� �������� �������� �� ���������
	void Equip() override;

	// ������� ��� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Main Stat"))
	EStatKey _ArmorKeyStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Stat Value"))
	int _ArmorValueStat;

private:

};

/// <summary>
/// ����������� ����� ��� ������.
/// ����������� ������ ������ - ������� ������� ����� ������.
/// </summary>
UCLASS(NotBlueprintable, Abstract)
class BROWSEPROJECT_API UWeapon : public UEquipment
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Weapon Mesh"))
	UStaticMesh* WeaponMesh;

public:

	// ������� ��� �������� �������� �� ���������
	void Equip() override;

	// ������� ��� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Weapon Additional Slot"))
	ESlotType _AdditionalSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Weapon Damage"))
	FWeaponDamage _WeaponDamage;

private:

};

/// <summary>
/// ����� ��� ���������� ������
/// �������� �������������� ������ ��� ���������.
/// ��������� ������ ���� ��� ���������.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UTwoHanded : public UWeapon
{

	GENERATED_BODY()

public:

	// ������� ��� �������� �������� �� ���������
	void Equip() override;

protected:



private:

};

/// <summary>
/// ����� ��� ����������� ������
/// �������� �������������� ������ ��� ���������.
/// ��������� ������ ���� ��� ��������� ������ ������ ���������� ��� ���������.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API USesquialteral : public UWeapon
{

	GENERATED_BODY()

public:

	// ������� ��� �������� �������� �� ���������
	void Equip() override;

protected:



private:

};

/// <summary>
/// ����� ��� ����������� ������
/// �������� �������������� ������ ��� ���������.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UOneHanded : public UWeapon
{

	GENERATED_BODY()

public:

	// ������� ��� �������� �������� �� ���������
	void Equip() override;

protected:



private:

};

/// <summary>
/// ����� ��� ���������.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UJewelry : public UEquipment
{

	GENERATED_BODY()

public:

	// ������� ��� �������� �������� �� ���������
	void Equip() override;

	// ������� ��� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

protected:



private:

};

/// <summary>
/// ����� ��� �����.
/// ������ ����� �������������� ���� ��� ���������.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API URing : public UJewelry
{

	GENERATED_BODY()

public:

	// ������� ��� �������� �������� �� ���������
	void Equip() override;

	// ������� ��� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

protected:



private:

};
