// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemObjects.h"
#include "BrowseProject/Character/InventoryInterface.h"
#include "BrowseProject/Character/EquipmentInteface.h"

bool UBasicItem::AddToInventory(AActor* PlayableActor)
{
	if (Cast<IInventory>(PlayableActor)) {
		IInventory::Execute_AddBasicItemToInventory(PlayableActor, this);
		return true;
	}
	return false;
}

bool UBasicItem::SetDataToObject(FItemDataRow* Data)
{
	if (Data == nullptr) {
		return false;
	}
	Name = Data->Name;
	Description = Data->Description;
	IconSet = Data->IconSet;
	Rarity = Data->Rarity;
	WorldMesh = Data->WorldMesh;
	_Cost = Data->Cost;
	_IsStackable = Data->IsStackable;
	_ID = Data->ID;
	return true;
}

bool UEquipmentItem::AddToInventory(AActor* PlayableActor)
{
	if (Cast<IInventory>(PlayableActor)) {
		IInventory::Execute_AddEquipItemToInventory(PlayableActor, this);
		return true;
	}
	return false;
}

bool UEquipmentItem::CheckRequirements(AActor* Character)
{
	return true;
}

bool UEquipmentItem::EquipAtSlotCheckStatus(AActor* Character)
{
	return true;
}

bool UEquipmentItem::WithdrawFromCharacter(AActor* Character)
{
	return true;
}

bool UEquipmentItem::ApplyAllStatsToCharacter(AActor* Character)
{
	return true;
}

bool UEquipmentItem::AnnulItemStatsFromCharacter(AActor* Character)
{
	return true;
}

bool UEquipmentItem::SetDataToObject(FItemDataRow* Data)
{
	UBasicItem::SetDataToObject(Data);
	FEquipmentDataRow* t;
	try {
		t = static_cast<FEquipmentDataRow*>(Data);
	}
	catch (...) {
		return false;
	}
	_ItemAffixes = t->Affixes;
	_ItemRequirements = t->Requirements;
	return true;
}

/// ************************
/// Броня
/// ************************

bool UArmor::EquipAtSlotCheckStatus(AActor* Character)
{
	auto eq_t = Cast<IEquipment>(Character);
	auto inv_t = Cast<IInventory>(Character);
	if (eq_t && inv_t) {
		FEquipmentSlot* slot_t = eq_t->GetSlotStructure(_Slot);
		if (slot_t == nullptr) {
			return false;
		}
		if ((*slot_t).Status <= ESlotStatus::BLOCKED) {
			return false;
		}
		// Проверяем есть ли предмет в слоте перед одеванием
		if ((*slot_t).Item) {
			// Снимаем одетый предмет
			(*slot_t).Item->WithdrawFromCharacter(Character);
		}
		IEquipment::Execute_EquipItemOnCharacter(Character, this, _Slot);
		IInventory::Execute_RemoveEquipItemFromInventoryByFind(Character, this);
		IEquipment::Execute_SetSkeletalMeshAsCharacterPart(Character, ComponentBodyMesh, _Slot);
		ApplyAllStatsToCharacter(Character);
		return true;
	}
	return false;
}

bool UArmor::WithdrawFromCharacter(AActor* Character)
{
	// Отмена всех эффектов предмета на персонаже
	AnnulItemStatsFromCharacter(Character);
	// Добавление предмета обратно в инвентарь
	auto inv_t = Cast<IInventory>(Character);
	if (inv_t) {
		IInventory::Execute_AddEquipItemToInventory(Character, this);
	}
	// Установка базовой модели части персонажа
	auto eq_t = Cast<IEquipment>(Character);
	if (eq_t) {
		IEquipment::Execute_WithdrawItemFromCharacterSlot(Character, _Slot);
		IEquipment::Execute_SetBasicSkeletalMeshAtSlot(Character, _Slot);
	}
	return true;
}

bool UArmor::SetDataToObject(FItemDataRow* Data)
{
	UEquipmentItem::SetDataToObject(Data);
	FArmorDataRow* t;
	try {
		t = static_cast<FArmorDataRow*>(Data);
	}
	catch (...) {
		return false;
	}
	ComponentBodyMesh = t->ComponentBodyMesh;
	_Slot = t->ArmorSlot;
	_ArmorKeyStat = t->ArmorKeyStat;
	_ArmorValueStat = t->ArmorValueStat;
	return true;
}

/// ************************
/// Кубики
/// ************************

// Переопределение функции для одевания предмета на персонажа
bool UDice::EquipAtSlotCheckStatus(AActor* Character)
{
	auto eq_t = Cast<IEquipment>(Character);
	auto inv_t = Cast<IInventory>(Character);
	if (eq_t && inv_t) {
		auto slot_t = IEquipment::Execute_GetDiceFromSlot(Character, _Slot);
		// Проверяем есть ли кубик в слоте перед одеванием
		if (slot_t) {
			// Снимаем одетый предмет
			slot_t->WithdrawFromCharacter(Character);
		}
		IEquipment::Execute_PutDiceInPocket(Character, _Slot, this);
		IInventory::Execute_RemoveEquipItemFromInventoryByFind(Character, this);
		ApplyAllStatsToCharacter(Character);
		return true;
	}
	return false;
}

// Переопределение функции для снятия предмета с персонажа
bool UDice::WithdrawFromCharacter(AActor* Character)
{
	// Отмена всех эффектов предмета на персонаже
	AnnulItemStatsFromCharacter(Character);
	// Добавление предмета обратно в инвентарь
	auto inv_t = Cast<IInventory>(Character);
	if (inv_t) {
		IInventory::Execute_AddEquipItemToInventory(Character, this);
	}
	auto eq_t = Cast<IEquipment>(Character);
	if (eq_t) {
		IEquipment::Execute_TakeOffDiceFromPocket(Character, _Slot);
	}
	return true;
}

// Функция для считывания данных из структуры
bool UDice::SetDataToObject(FItemDataRow* Data)
{
	FDiceDataRow* data_t;
	try {
		data_t = static_cast<FDiceDataRow*>(Data);
		_Facets = data_t->Facets;
		_Slot = data_t->DiceSlot;
		return UEquipmentItem::SetDataToObject(Data);
	}
	catch (...) {
		return false;
	}
}

// Переопределение функции ролла значений кубика
int32 UDice::Roll_Implementation()
{
	int32 num_t = _Facets.Num();
	if (num_t <= 0)
	{
		return 1;
	}
	return _Facets[FMath::RandRange(0, num_t - 1)];
}

/// ************************
/// Оружие
/// ************************

bool UWeapon::SetDataToObject(FItemDataRow* Data)
{
	UEquipmentItem::SetDataToObject(Data);
	FWeaponDataRow* t;
	try {
		t = static_cast<FWeaponDataRow*>(Data);
	}
	catch (...) {
		return false;
	}
	WeaponMesh = t->WeaponMesh;
	_WeaponDamage = t->WeaponDamage;
	return true;
}

