// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemObjects.h"
#include "BrowseProject/Character/InventoryInterface.h"
#include "BrowseProject/Character/EquipmentInteface.h"

void UBasicItem::AddToInventory(AActor* PlayableActor)
{
	if (Cast<IInventory>(PlayableActor)) {
		IInventory::Execute_AddBasicItemToInventory(PlayableActor, this);
	}
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

void UEquipmentItem::AddToInventory(AActor* PlayableActor)
{
	if (Cast<IInventory>(PlayableActor)) {
		IInventory::Execute_AddEquipItemToInventory(PlayableActor, this);
	}
}

bool UEquipmentItem::CheckRequirements()
{
	return true;
}

void UEquipmentItem::Equip(AActor* Character)
{
	return;
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
	_Slot = t->Slot;
	_ItemRequirements = t->Requirements;
	return true;
}

ESlotType UEquipmentItem::GetItemSlot() const
{
	return _Slot;
}

void UArmor::Equip(AActor* Character)
{
	if (Cast<IEquipment>(Character)) {
		IEquipment::Execute_EquipItemOnCharacter(Character, this, ESlotStatus::DEFAULT);
		IEquipment::Execute_SetSkeletalMeshAsCharacterPart(Character, ComponentBodyMesh, _Slot);
	}
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
	_ArmorKeyStat = t->ArmorKeyStat;
	_ArmorValueStat = t->ArmorValueStat;
	return true;
}

void UWeapon::Equip(AActor* Character)
{
	UEquipmentItem::Equip(Character);
}

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
	_AdditionalSlot = t->AdditionalSlot;
	_WeaponDamage = t->WeaponDamage;
	return true;
}

void UOneHanded::Equip(AActor* Character)
{
	UEquipmentItem::Equip(Character);
}

void UTwoHanded::Equip(AActor* Character)
{
	UEquipmentItem::Equip(Character);
}

void USesquialteral::Equip(AActor* Character)
{
	UEquipmentItem::Equip(Character);
}

void UJewelry::Equip(AActor* Character)
{
	UEquipmentItem::Equip(Character);
}

bool UJewelry::SetDataToObject(FItemDataRow* Data)
{
	return UEquipmentItem::SetDataToObject(Data);
}

void URing::Equip(AActor* Character)
{
	UEquipmentItem::Equip(Character);
}

bool URing::SetDataToObject(FItemDataRow* Data)
{
	return UJewelry::SetDataToObject(Data);
}

