// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "BrowseProject/ItemSystem/ItemObjects.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = false;

	_EquipmentSlots.Add(ESlotType::HEAD, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::BODY, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::HANDS, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::LEGS, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::FEET, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::FINGER_1, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::FINGER_2, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::NECKLACE, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::WRIST, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::LEFT_HAND, FEquipmentSlot(nullptr, ESlotStatus::DEFAULT));
	_EquipmentSlots.Add(ESlotType::RIGHT_HAND, FEquipmentSlot(nullptr, ESlotStatus::TWOHANDED));
	// ...
}

FEquipOperationStatus UEquipmentComponent::SetItemInSlot(ESlotType Slot, UEquipmentItem* Item, ESlotStatus Status)
{
	if (Item == nullptr) {
		return FEquipOperationStatus("There is no item for equip!", false);
	}

	if (Item->GetItemSlot() == Slot) {
		auto S = _EquipmentSlots.Find(Slot);

		if (S == nullptr) return FEquipOperationStatus("Incorrect slot type was used to equip!", false);

		if (S->Status >= Status) {
			S->Item = Item;
			return FEquipOperationStatus("Success!", true);
		}
		else {
			return FEquipOperationStatus("Status of Slot does not match with item slot status!", false);
		}
	}
	else {
		return FEquipOperationStatus("Incorrect slot type was used to equip!", false);
	}
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

TMap<ESlotType, FEquipmentSlot> UEquipmentComponent::GetEquipmentSlots() const
{
	return _EquipmentSlots;
}

FEquipmentSlot UEquipmentComponent::GetEquipmentSlot(ESlotType Slot) const
{
	return _EquipmentSlots.FindChecked(Slot);
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

