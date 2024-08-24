// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrowseProject/General/Items/Data/ItemData.h"
#include "BrowseProject/Character/Components/EquipmentComponent.h"
#include "BrowseProject/Character/Components/InventoryComponent.h"
#include "BrowseProject/General/Items/Interface/Roll.h"
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

	/// <summary>
	/// ������� ���������� �������� � ���������
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� ���������</param>
	/// <returns>���������� ��� �� �������� �������</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool AddToInventory(AActor* Character);

	/// <summary>
	/// �������, ������� ��������� ��� ������ �� ��������������� ���������
	/// </summary>
	/// <param name="Data">��������� ������</param>
	/// <returns>��������� ��������</returns>
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
	/// ���������� �������� � ���� � ��������� ������� �����
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� ����������</param>
	/// <returns>���������� ��� ���� ������� � ����</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool EquipAtCharacterSlot(AActor* Character) const;

	/// <summary>
	/// ������ �������� � ���������
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� ����������</param>
	/// <returns>���������� ������� �� ����� �������</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool WithdrawFromCharacterSlot(AActor* Character) const;

	/// <summary>
	/// ��������� ��� �������������� �������� � ���������
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� �������������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	virtual bool ApplyAllStatsToCharacter(AActor* Character) const;

	/// <summary>
	/// �������� ��� ��������������, ������� ���� ��������� � ��������� � ��������
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� �������������</param>
	/// <returns>���������� ��������� ��������</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool AnnulItemStatsFromCharacter(AActor* Character) const;

	/// <summary>
	/// ����������� �������, ������������ ��� �����
	/// </summary>
	/// <returns>��� ����� � ������� ESlotType</returns>
	/// UFUNCTION(BlueprintCallable)
	virtual ESlotType GetItemSlot() const;

public:

	// ��������������� ���������� �������� � ���������
	virtual bool AddToInventory(AActor* Character) override;

	// ��������������� ������� ���������� ������ �� ���������
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

	// ��������������� ������� ��� �������� �������� �� ���������
	virtual bool EquipAtCharacterSlot(AActor* Character) const override;

	// ��������������� ������� ��� ������ �������� � ���������
	virtual bool WithdrawFromCharacterSlot(AActor* Character) const override;

	// ��������������� ������� ���������� ������������� � ���������
	//virtual bool ApplyAllStatsToCharacter(AActor* Character) override;

	// ��������������� ������� ������ ����������� ������������� � ���������
	//virtual bool AnnulItemStatsFromCharacter(AActor* Character) override;

	// ������� ��� ���������� ������ �� ���������
	virtual bool SetDataToObject(FItemDataRow* Data) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Main Stat"))
	EStatKey _ArmorKeyStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Stat Value"))
	int _ArmorValueStat;

private:

};

/// <summary>
/// ����� ������
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UDice : public UEquipmentItem
{

	GENERATED_BODY()

public:

	// ��������������� ������� ��� �������� �������� �� ���������
	virtual bool EquipAtCharacterSlot(AActor* Character) const override;

	// ��������������� ������� ��� ������ �������� � ���������
	virtual bool WithdrawFromCharacterSlot(AActor* Character) const override;

	// ������� ��� ���������� ������ �� ���������
	virtual bool SetDataToObject(FItemDataRow* Data) override;

	// ��������������� ������� ����� �������� ������
	UFUNCTION(BlueprintCallable)
	int32 Roll() const;

private:

	UPROPERTY(VisibleAnywhere, Category = "Dice Stats", meta = (DisplayName = "Map of Facets on Dice"))
	TArray<int32> _Facets;
};

/// <summary>
/// ����������� ����� ��� ������.
/// ����������� ������ ������ - ������� ������� ����� ������.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UWeapon : public UEquipmentItem
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Item Appearance", Meta = (DisplayName = "Weapon Appearance"))
	FWeaponAppearance WeaponAppearance;

public:

	// ������� ��� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

	// ��������������� ������� ��� �������� �������� �� ���������
	virtual bool EquipAtCharacterSlot(AActor* Character) const override;

	// ��������������� ������� ��� ������ �������� � ���������
	virtual bool WithdrawFromCharacterSlot(AActor* Character) const override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Weapon Damage"))
	FWeaponDamage _WeaponDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Weapon Class"))
	EWeaponType _WeaponClass;

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

protected:

private:

};

/// <summary>
/// ����� ��� �����.
/// ������ ����� �������������� ���� ��� ���������.
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API URing : public UEquipmentItem
{

	GENERATED_BODY()

public:


protected:


private:

};
