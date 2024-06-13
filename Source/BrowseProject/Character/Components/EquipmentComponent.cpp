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
	_EquipmentSlots.Add(ESlotType::HEAD, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::BODY, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::HANDS, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::LEGS, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::FEET, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::FINGER_1, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::FINGER_2, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::NECKLACE, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::WRIST, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::LEFT_HAND, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::RIGHT_HAND, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT, ESlotStatus::DEFAULT));
	// ...

	_DiceList.Add(EDice::ATTACK_DICE, nullptr);
	_DiceList.Add(EDice::DAMAGE_DICE, nullptr);
	_DiceList.Add(EDice::TRIAL_DICE, nullptr);
}

bool UEquipmentComponent::SetItemInSlot(ESlotType Slot, UEquipmentItem* Item)
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
	(*find_t).Item = Item;
	return true;
}

UEquipmentItem* UEquipmentComponent::WithdrawItemFromSlot(ESlotType Slot)
{
	auto S = _EquipmentSlots.Find(Slot);
	if (S == nullptr) {
		return nullptr;
	}

	auto ReturnItem = S->Item;
	S->Item = nullptr;

	return ReturnItem;
}

UEquipmentItem* UEquipmentComponent::GetEquipmentItemFromList(ESlotType Slot)
{
	auto item_t = _EquipmentSlots.Find(Slot);
	if (item_t) {
		return (*item_t).Item;
	}
	else {
		return nullptr;
	}
}

TMap<ESlotType, FEquipmentSlot> UEquipmentComponent::GetEquipmentSlotList() const
{
	return _EquipmentSlots;
}

FEquipmentSlot* UEquipmentComponent::GetEquipmentSlot(ESlotType Slot)
{
	return _EquipmentSlots.Find(Slot);
}

bool UEquipmentComponent::SetDiceInSlot(EDice Slot, UDice* Dice)
{
	auto dice_d = _DiceList.Find(Slot);
	if (dice_d) {
		(*dice_d) = Dice;
		return true;
	}
	else {
		return false;
	}
}


UDice* UEquipmentComponent::GetDiceFromSlot(EDice Slot) const
{
	auto dice_d = _DiceList.Find(Slot);
	if (dice_d) {
		return *dice_d;
	}
	else {
		return nullptr;
	}
}

TMap<EDice, UDice*> UEquipmentComponent::GetDiceList() const
{
	return _DiceList;
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

