// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "EquipmentComponent.h"
#include "BrowseProject/UI/Item/ItemTag.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	_CachedItem = nullptr;
	// ...
}

	
// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TSubclassOf<UItemTag> UInventoryComponent::GetClassOfItemTag()
{
	return _UsedTypeOfItemTag;
}

void UInventoryComponent::DisplayItems() const 
{
	if (_OnDisplayItemsDelegate.IsBound()) {
		_OnDisplayItemsDelegate.Broadcast();
	}
}

void UInventoryComponent::HideItems() const 
{
	if (_OnHideItemsDelegate.IsBound()) {
		_OnHideItemsDelegate.Broadcast();
	}
}

void UInventoryComponent::AddEquipItemAtList(const UEquipmentItem* Item)
{
	if (Item) {
		_EquipmentItemList.Add(Item);
	}
}

const UEquipmentItem* UInventoryComponent::GetEquipmentItemFromListByIndex(int32 Index) const
{
	if (_EquipmentItemList.Num() <= Index || Index < 0) {
		return nullptr;
	}
	else {
		return _EquipmentItemList[Index];
	}
}

const UEquipmentItem* UInventoryComponent::RemoveEquipmentItemFromListByIndex(int32 Index)
{
	// Проверка индекса
	if (_EquipmentItemList.Num() <= Index || Index < 0) {
		return nullptr;
	}
	// Проверка есть ли предмет по индексу
	auto RemovableItem = _EquipmentItemList[Index];

	if (RemovableItem == nullptr) {
		return nullptr;
	}

	_EquipmentItemList.RemoveAt(Index);

	return RemovableItem;
		
}

bool UInventoryComponent::RemoveEquipmentItemFromListByFind(const UEquipmentItem* RemoveItem)
{
	int32 Index;
	if (_EquipmentItemList.Find(RemoveItem, Index) == true) {
		_EquipmentItemList.RemoveAt(Index);
		return true;
	}
	return false;
}

const TArray<const UEquipmentItem*>& UInventoryComponent::GetEquipmentItemList() const
{
	return _EquipmentItemList;
}

int32 UInventoryComponent::GetCountOfEquipItems() const
{
	return _EquipmentItemList.Num();
}

FOnDisplayItemsSignature& UInventoryComponent::GetDisplaySignature()
{
	return _OnDisplayItemsDelegate;
}

FOnHideItemsSignature& UInventoryComponent::GetHideSignature()
{
	return _OnHideItemsDelegate;
}