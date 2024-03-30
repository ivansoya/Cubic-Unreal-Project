// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemObjects.h"

void UBasicItem::AddToInventory()
{

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

bool UEquipment::CheckRequirements()
{
	return true;
}

void UEquipment::Equip()
{

}

bool UEquipment::SetDataToObject(FItemDataRow* Data)
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

void UArmor::Equip()
{
	UEquipment::Equip();
}

bool UArmor::SetDataToObject(FItemDataRow* Data)
{
	UEquipment::SetDataToObject(Data);
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

void UWeapon::Equip()
{
	UEquipment::Equip();
}

bool UWeapon::SetDataToObject(FItemDataRow* Data)
{
	UEquipment::SetDataToObject(Data);
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

void UOneHanded::Equip()
{
	UEquipment::Equip();
}

void UTwoHanded::Equip()
{
	UEquipment::Equip();
}

void USesquialteral::Equip()
{
	UEquipment::Equip();
}

void UJewelry::Equip() 
{
	UEquipment::Equip();
}

bool UJewelry::SetDataToObject(FItemDataRow* Data)
{
	return UEquipment::SetDataToObject(Data);
}

void URing::Equip()
{
	UEquipment::Equip();
}

bool URing::SetDataToObject(FItemDataRow* Data)
{
	return UJewelry::SetDataToObject(Data);
}

