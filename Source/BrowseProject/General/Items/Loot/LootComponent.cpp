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

		// �������� �� �����������. ���� ������ - ������� ���������, ����� continue
		if (FMath::RandRange(MIN_CHANCE, MAX_CHANCE) > t.SpawnChance) {
			continue;
		}

		// �������� �� ������������� �������
		if (t.ItemSource.DataTable == nullptr) {
			continue;
		}

		// ����������� ������ ��������
		// ��������� �������� �� ������� �������
		FItemDataRow* Data = CastFindStruct<FItemDataRow>(t.ItemSource.DataTable, t.ItemSource.RowName);
		if (Data != nullptr) {
			ItemObject = NewObject<UBasicItem>();
			SpawnItemAtWorld(ItemObject, Data, SpawnTransform);
			continue;
		}
		// ��������� �������� �� ������� ������
		Data = CastFindStruct<FArmorDataRow>(t.ItemSource.DataTable, t.ItemSource.RowName);
		if (Data != nullptr) {
			ItemObject = NewObject<UArmor>();
			SpawnItemAtWorld(ItemObject, Data, SpawnTransform);
			continue;
		}
		// ��������� �������� �� ������� �������
		Data = CastFindStruct<FWeaponDataRow>(t.ItemSource.DataTable, t.ItemSource.RowName);
		if (Data != nullptr) {
			// ������������ �������� ����� ����
			EWeaponType ewt = static_cast<FWeaponDataRow*>(Data)->WeaponClass;
			if (ewt == EWeaponType::STAFF || ewt == EWeaponType::BOW || ewt == EWeaponType::TWOHANDED_SWORD) {
				ItemObject = NewObject<UTwoHanded>();
			}
			else if (ewt == EWeaponType::ONEHANDED_SWORD || ewt == EWeaponType::DAGGER) {
				ItemObject = NewObject<UOneHanded>();
			}
			else {
				ItemObject = NewObject<USesquialteral>();
			}
			// ����� ������������ ��������� ����� ����
			SpawnItemAtWorld(ItemObject, Data, SpawnTransform);
			continue;
		}
		// ��������� �������� �� ������� ����������
		Data = CastFindStruct<FJewelryDataRow>(t.ItemSource.DataTable, t.ItemSource.RowName);
		if (Data != nullptr) {
			ItemObject = NewObject<UJewelry>();
			SpawnItemAtWorld(ItemObject, Data, SpawnTransform);
			continue;
		}
		// ��������� �������� �� ������� �������
		Data = CastFindStruct<FRingDataRow>(t.ItemSource.DataTable, t.ItemSource.RowName);
		if (Data != nullptr) {
			ItemObject = NewObject<URing>();
			SpawnItemAtWorld(ItemObject, Data, SpawnTransform);
			continue;
		}
		// ��������� �������� ��� ������� �������
		Data = CastFindStruct<FDiceDataRow>(t.ItemSource.DataTable, t.ItemSource.RowName);
		if (Data != nullptr) {
			ItemObject = NewObject<UDice>();
			SpawnItemAtWorld(ItemObject, Data, SpawnTransform);
		}
		// ��������� ������ � ����������� ������ ��������
		//else {
		//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Error"));
		//	continue;
		//}
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



