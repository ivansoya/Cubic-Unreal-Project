// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "BrowseProject/Character/EquipmentComponent.h"
#include "BrowseProject/Character/InventoryComponent.h"
#include "Roll.h"
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
	/// �������, ������� ��������� �������� �� �������
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� �������������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	bool CheckRequirements(AActor* Character);

	/// <summary>
	/// ���������� �������� � ���� � ��������� ������� �����
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� ����������</param>
	/// <returns>���������� ��� ���� ������� � ����</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool EquipAtSlotCheckStatus(AActor* Character);

	/// <summary>
	/// ������ �������� � ���������
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� ����������</param>
	/// <returns>���������� ������� �� ����� �������</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool WithdrawFromCharacter(AActor* Character);

	/// <summary>
	/// ��������� ��� �������������� �������� � ���������
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� �������������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	virtual bool ApplyAllStatsToCharacter(AActor* Character);

	/// <summary>
	/// �������� ��� ��������������, ������� ���� ��������� � ��������� � ��������
	/// </summary>
	/// <param name="Character">����� ������, � �������� ��������� ���������� �������������</param>
	/// <returns>���������� ��������� ��������</returns>
	UFUNCTION(BlueprintCallable)
	virtual bool AnnulItemStatsFromCharacter(AActor* Character);

	/// <summary>
	/// ����������� �������, ������������ ��� �����
	/// </summary>
	/// <returns>��� ����� � ������� ESlotType</returns>
	ESlotType GetItemSlot() const;

public:

	// ��������������� ���������� �������� � ���������
	virtual bool AddToInventory(AActor* Character) override;

	// ��������������� ������� ���������� ������ �� ���������
	bool SetDataToObject(FItemDataRow* Data) override;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "List of Item Affixes"))
	TArray<UAffix*> _ItemAffixes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "List of Requirements"))
	TMap<EStatKey, int> _ItemRequirements;

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
	virtual bool EquipAtSlotCheckStatus(AActor* Character) override;

	// ��������������� ������� ��� ������ �������� � ���������
	virtual bool WithdrawFromCharacter(AActor* Character) override;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Item Slot"))
	ESlotType _Slot;

private:

};

/// <summary>
/// ����� ������
/// </summary>
UCLASS(Blueprintable)
class BROWSEPROJECT_API UDice : public UEquipmentItem, public IRoll
{

	GENERATED_BODY()

public:

	// ��������������� ������� ��� �������� �������� �� ���������
	virtual bool EquipAtSlotCheckStatus(AActor* Character) override;

	// ��������������� ������� ��� ������ �������� � ���������
	virtual bool WithdrawFromCharacter(AActor* Character) override;

	// ������� ��� ���������� ������ �� ���������
	virtual bool SetDataToObject(FItemDataRow* Data) override;

	// ��������������� ������� ����� �������� ������
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 Roll();

private:

	UPROPERTY(VisibleAnywhere, Category = "Dice Stats", meta = (DisplayName = "Map of Facets on Dice"))
	TArray<int32> _Facets;

	UPROPERTY(VisibleAnywhere, Category = "Dice Stats", meta = (DisplayName = "Slot"))
	EDice _Slot;
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


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Stats", Meta = (DisplayName = "Item Slot"))
	ESlotType _Slot;

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
