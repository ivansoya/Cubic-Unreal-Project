// Fill out your copyright notice in the Description page of Project Settings.


#include "LootComponent.h"
#include "BrowseProject/UI/Item/ItemTag.h"

// Sets default values for this component's properties
ULootComponent::ULootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULootComponent::SpawnLoot(FTransform SpawnTransform)
{
	if (LootType == ELootType::ELT_Custom) {
		SpawnCustomLoot(SpawnTransform);
	}
	else if (LootType == ELootType::ELT_LootDataTable) {
		SpawnLootFromLootTable(SpawnTransform);
	}
}

void ULootComponent::SpawnCustomLoot(FTransform SpawnTransform)
{
	UBasicItem* ItemObject;
	for (auto& t : CustomLootList) {

		// Проверка на вероятность. Если прошло - предмет спавнится, иначе continue
		if (FMath::RandRange(MIN_CHANCE, MAX_CHANCE) > t.SpawnChance) {
			continue;
		}

		// Проверка на существование таблицы
		if (t.ItemSource.DataTable == nullptr) {
			continue;
		}

		// Определение класса предмета
		// Проверяем является ли предмет базовым
		FItemDataRow* Data = CastFindStruct<FItemDataRow>(t.ItemSource.DataTable, t.ItemSource.RowName);
		if (Data != nullptr) {
			ItemObject = NewObject<UBasicItem>();
			SpawnItemAtWorld(ItemObject, Data, SpawnTransform);
			continue;
		}
		// Проверяем является ли предмет экипируемым
		Data = CastFindStruct<FEquipmentDataRow>(t.ItemSource.DataTable, t.ItemSource.RowName);
		if (Data != nullptr) {
			// Смотрим тип предмеиа и создаем соответсвующий предмет
			switch (static_cast<FEquipmentDataRow*>(Data)->ItemType) {
				case EEquipmentItemType::WEAPON:
					ItemObject = NewObject<UWeapon>();
					break;
				case EEquipmentItemType::ARMOR:
					ItemObject = NewObject<UArmor>();
					break;
				case EEquipmentItemType::ONESLOT_JEWELERY:
					ItemObject = NewObject<UJewelry>();
					break;
				case EEquipmentItemType::RING:
					ItemObject = NewObject<URing>();
					break;
				case EEquipmentItemType::DICE:
					ItemObject = NewObject<UDice>();
					break;
				default:
					// Если никакой предмет не подошел по типу - пропуск
					continue;
					break;
			}
			// Спавн предмета в мире
			SpawnItemAtWorld(ItemObject, Data, SpawnTransform);
			continue;
		}
	}
}

void ULootComponent::SpawnLootFromLootTable(FTransform SpawnTransform)
{

}

AWorldItem* ULootComponent::SpawnItemAtWorld(UBasicItem*& ItemObject, FItemDataRow* Data, 
	FTransform SpawnTransform, const wchar_t* TextOnSuccess, const wchar_t* TextOnError)
{
	if (ItemObject->SetDataToObject(Data) == true) {
		AWorldItem* Spawned = GetWorld()->SpawnActorDeferred<AWorldItem>(AWorldItem::StaticClass(), SpawnTransform);
		Spawned->ItemObject = ItemObject;
		Spawned->FinishSpawning(SpawnTransform);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TextOnSuccess);
		return Spawned;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TextOnError);
		ItemObject->MarkAsGarbage();
		ItemObject = nullptr;
		return nullptr;
	}
}

template<typename T>
T* ULootComponent::CastFindStruct(TObjectPtr<const UDataTable> DataTable, FName RowName) {
	if (DataTable->GetRowStruct() == T::StaticStruct()) {
		T* Data = DataTable->FindRow<T>(RowName, "");
		return Data;
	}
	return nullptr;
}

// Called when the game starts
void ULootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



