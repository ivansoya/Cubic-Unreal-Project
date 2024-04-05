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

	UFUNCTION(BlueprintCallable)
	virtual void AddToInventory(AActor* PlayableActor);

	// ������� ��� ���������� ������ �� ���������
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

	virtual void AddToInventory(AActor* PlayableActor) override;

	// ������� ��� �����������, ����� �� ������ ������� �� ���������
	UFUNCTION(BlueprintCallable)
	bool CheckRequirements();

	// ������� ��� �������� �������� �� ���������
	UFUNCTION(BlueprintCallable)
	virtual void Equip(AActor* Chacter);

	// ������� ��� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

	ESlotType GetItemSlot() const;

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
class BROWSEPROJECT_API UArmor : public UEquipmentItem
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Body Mesh"))
	USkeletalMesh* ComponentBodyMesh;

public:

	// ������� ��� �������� �������� �� ���������
	void Equip(AActor* Character) override;

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
class BROWSEPROJECT_API UWeapon : public UEquipmentItem
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Weapon Mesh"))
	UStaticMesh* WeaponMesh;

public:

	// ������� ��� �������� �������� �� ���������
	void Equip(AActor* Character) override;

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
	void Equip(AActor* Character) override;

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
	void Equip(AActor* Character) override;

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
	void Equip(AActor* Character) override;

protected:



private:

};

/// <summary>
/// ����� ��� ���������.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UJewelry : public UEquipmentItem
{

	GENERATED_BODY()

public:

	// ������� ��� �������� �������� �� ���������
	void Equip(AActor* Character) override;

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
	void Equip(AActor* Character) override;

	// ������� ��� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

protected:



private:

};
