// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "BrowseProject/General/Items/Objects/ItemObjects.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = false;

	// Инициализация всех слотов экипировки
	_EquipmentSlots.Add(ESlotType::WEAPON, nullptr);
	_EquipmentSlots.Add(ESlotType::HEAD, nullptr);
	_EquipmentSlots.Add(ESlotType::BODY, nullptr);
	_EquipmentSlots.Add(ESlotType::HANDS, nullptr);
	_EquipmentSlots.Add(ESlotType::LEGS, nullptr);
	_EquipmentSlots.Add(ESlotType::FEET, nullptr);
	_EquipmentSlots.Add(ESlotType::FINGER_1, nullptr);
	_EquipmentSlots.Add(ESlotType::FINGER_2, nullptr);
	_EquipmentSlots.Add(ESlotType::NECKLACE, nullptr);
	_EquipmentSlots.Add(ESlotType::WRIST, nullptr);
	_EquipmentSlots.Add(ESlotType::ATTACK_DICE, nullptr);
	_EquipmentSlots.Add(ESlotType::DAMAGE_DICE, nullptr);
	_EquipmentSlots.Add(ESlotType::TRIAL_DICE, nullptr);
}

bool UEquipmentComponent::SetItemInSlot(ESlotType Slot, const UEquipmentItem* Item)
{
	// Проверяем переданный предмет на нуль
	if (Item == nullptr) {
		return false;
	}
	// Проверяем существует ли такой слот
	auto find_t = _EquipmentSlots.Find(Slot);
	if (find_t == nullptr) {
		return false;
	}
	// Устанавливаем в слот предмет
	_EquipmentSlots[Slot] = Item;
	return true;
}

const UEquipmentItem* UEquipmentComponent::WithdrawItemFromSlot(ESlotType Slot)
{
	if (_EquipmentSlots.Contains(Slot) == true) {
		auto w_item = _EquipmentSlots[Slot];
		_EquipmentSlots[Slot] = nullptr;
		return w_item;
	}
	else {
		return nullptr;
	}
}

const UEquipmentItem* UEquipmentComponent::GetEquipmentItemFromList(ESlotType Slot) const
{
	if (_EquipmentSlots.Contains(Slot) == true)
	{
		return _EquipmentSlots[Slot];
	}
	else {
		return nullptr;
	}
}

const TMap<ESlotType, const UEquipmentItem*>& UEquipmentComponent::GetEquipmentList() const
{
	return _EquipmentSlots;
}


const UDice* UEquipmentComponent::GetDiceFromSlot(ESlotType Slot) const
{
	// Проверка, что слот - нужный
	if (Slot == ESlotType::TRIAL_DICE || Slot == ESlotType::DAMAGE_DICE || Slot == ESlotType::TRIAL_DICE) {
		// Находим кубик по слоту
		auto t_dice = _EquipmentSlots.Find(Slot);
		if (*t_dice == nullptr) {
			return nullptr;
		}
		else {
			// Возвращаем нужный тип объекта кубика
			return Cast<UDice>(*t_dice);
		}
	}
	else {
		return nullptr;
	}
}

const TMap<ESlotType, const UDice*> UEquipmentComponent::GetDiceList() const
{
	TMap<ESlotType, const UDice*> DiceList = {
		{ESlotType::ATTACK_DICE, GetDiceFromSlot(ESlotType::ATTACK_DICE)},
		{ESlotType::ATTACK_DICE, GetDiceFromSlot(ESlotType::DAMAGE_DICE)},
		{ESlotType::ATTACK_DICE, GetDiceFromSlot(ESlotType::TRIAL_DICE)},
	};
	return DiceList;
}

// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

