// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemObjects.h"
#include "BrowseProject/Character/Interfaces/Stat.h"
#include "BrowseProject/Character/Interfaces/Inventory.h"
#include "BrowseProject/Character/Interfaces/Equipment.h"

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

bool UEquipmentItem::EquipAtCharacterSlot(AActor* Character) const
{
	return true;
}

bool UEquipmentItem::WithdrawFromCharacterSlot(AActor* Character) const
{
	return true;
}

bool UEquipmentItem::ApplyAllStatsToCharacter(AActor* Character) const
{
	for (auto t_Affix : _ItemAffixes) {
		IAffix::Execute_Apply(t_Affix, Character);
	}
	return true;
}

bool UEquipmentItem::AnnulItemStatsFromCharacter(AActor* Character) const
{
	for (auto t_Affix : _ItemAffixes) {
		IAffix::Execute_Cancel(t_Affix, Character);
	}
	return true;
}

bool UEquipmentItem::SetDataToObject(FItemDataRow* Data)
{
	if (UBasicItem::SetDataToObject(Data) == false) {
		return false;
	}
	try {
		_ItemData = static_cast<FEquipmentDataRow*>(Data);
	}
	catch (...) {
		return false;
	}
	for (auto& t_Row : _ItemData->Affixes) {
		auto t_aff = UItemDataFunctionLibrary::SpawnAffixFromTableRow(t_Row.AffixDataRow.DataTable, t_Row.AffixDataRow.RowName, t_Row.Tier);
		if (t_aff) {
			_ItemAffixes.Add(t_aff);
		}
	}
	_ItemRequirements = _ItemData->Requirements;
	return true;
}

ESlotType UEquipmentItem::GetItemSlot() const
{
	return ESlotType::NONE_TYPE;
}

/// ************************
/// Броня
/// ************************

bool UArmor::EquipAtCharacterSlot(AActor* Character) const 
{
	// Проверка на нужные интерфейсы у персонажа
	auto eq_t = Cast<IEquipment>(Character);
	auto stat_t = Cast<IStatInterface>(Character);
	if ((eq_t || stat_t) == false) {
		return false;
	}
	// Одеваем предмет в слот
	IEquipment::Execute_EquipItemOnCharacter(Character, this, _Slot);
	IEquipment::Execute_SetSkeletalMeshAsCharacterPart(Character, ComponentBodyMesh, _Slot);
	ApplyAllStatsToCharacter(Character);
	return true;
}

bool UArmor::WithdrawFromCharacterSlot(AActor* Character) const
{
	// Проверяем есть ли нужные интерфейсы на персонаже:
	auto eq_t = Cast<IEquipment>(Character);
	auto st_t = Cast<IStatInterface>(Character);
	if ((eq_t || st_t) == false) {
		return false;
	}
	// Вызов функции снятия предмета со слота экипировки
	IEquipment::Execute_WithdrawItemFromCharacterSlot(Character, _Slot);
	// Установка базового внешнего вида модели персонажа
	IEquipment::Execute_SetBasicSkeletalMeshAtSlot(Character, _Slot);
	// Отмена всех эффектов предмета на персонаже
	AnnulItemStatsFromCharacter(Character);
	return true;
}

bool UArmor::SetDataToObject(FItemDataRow* Data)
{
	if (UEquipmentItem::SetDataToObject(Data) == false || _ItemData == nullptr) {
		return false;
	}
	_Slot = _ItemData->ArmorSlot;
	ComponentBodyMesh = _ItemData->ComponentBodyMesh;
	_ArmorKeyStat = _ItemData->ArmorKeyStat;
	_ArmorValueStat = _ItemData->ArmorValueStat;
	return true;
}

/// ************************
/// Кубики
/// ************************

// Переопределение функции для одевания предмета на персонажа
bool UDice::EquipAtCharacterSlot(AActor* Character) const
{
	// Проверка на нужные интерфейсы у персонажа
	auto eq_t = Cast<IEquipment>(Character);
	auto stat_t = Cast<IStatInterface>(Character);
	if ((eq_t || stat_t) == false) {
		return false;
	}
	// Одеваем предмет в слот
	IEquipment::Execute_EquipItemOnCharacter(Character, this, _Slot);
	// Установка статов к персонажу
	ApplyAllStatsToCharacter(Character);
	return true;
}

// Переопределение функции для снятия предмета с персонажа
bool UDice::WithdrawFromCharacterSlot(AActor* Character) const
{
	// Проверяем есть ли нужные интерфейсы на персонаже:
	auto eq_t = Cast<IEquipment>(Character);
	auto st_t = Cast<IStatInterface>(Character);
	if ((eq_t || st_t) == false) {
		return false;
	}
	// Вызов функции снятия предмета со слота экипировки
	IEquipment::Execute_WithdrawItemFromCharacterSlot(Character, _Slot);
	// Отмена всех эффектов предмета на персонаже
	AnnulItemStatsFromCharacter(Character);
	return true;
}

// Функция для считывания данных из структуры
bool UDice::SetDataToObject(FItemDataRow* Data)
{
	if (UEquipmentItem::SetDataToObject(Data) == false || _ItemData == nullptr) {
		return false;
	}
	_Slot = _ItemData->DiceSlot;
	_Facets = _ItemData->Facets;
	return true;
}

// Переопределение функции ролла значений кубика
int32 UDice::Roll() const
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
	if (UEquipmentItem::SetDataToObject(Data) == false || _ItemData == nullptr) {
		return false;
	}
	WeaponAppearance = _ItemData->WeaponMeshes;
	_WeaponDamage = _ItemData->WeaponDamage;
	_WeaponClass = _ItemData->WeaponClass;
	return true;
}

