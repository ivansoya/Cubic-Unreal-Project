// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "EquipmentComponent.h"
#include "BrowseProject/UI/ItemTag.h"

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

void UInventoryComponent::AddEquipItem(UEquipmentItem* Item) 
{
	if (Item) {
		_EquipmentItemList.Add(FEquipItemSlotInv(Item, false));
	}
}

TArray<FEquipItemSlotInv> UInventoryComponent::GetEquipmentItemList() const
{
	return _EquipmentItemList;
}

int32 UInventoryComponent::GetCountOfEquipItems()
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