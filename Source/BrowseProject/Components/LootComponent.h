// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Templates/SubclassOf.h"
#include "BrowseProject/ItemSystem/WorldItem.h"
#include "LootComponent.generated.h"

#define MIN_CHANCE 0
#define MAX_CHANCE 1000

class UItemTag;

USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FLootRow
{
	GENERATED_BODY()

	// MinChance = 0, MaxChance = 1000;
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Item Drop Chance", ClampMin = "0", ClampMax = "1000"))
	int SpawnChance;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Item Source"))
	FDataTableRowHandle ItemSource;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Is the subject a single?"))
	bool IsSingle = true;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Min Count?", EditCondition = "IsSingle == false"))
	int MinCount;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Max Count?", EditCondition = "IsSingle == false"))
	int MaxCount;
};

UENUM(Meta = (Bitflags))
enum class ELootType : uint8
{
	ELT_Custom UMETA(DisplayName = "Custom Loot"),
	ELT_LootDataTable UMETA(DisplayName = "From Loot Table"),
};

/* 
* �����-���������� ��� ����.
* ����� ��� ������ ��������� ����� ������ ����� ��� ���������� ��������.
* ��������� �� ����������� ���� �������.
* ������ ���� � �������� ��������� ����� ������ - OtherItemsDataTable, EquipmentDataTable, WeaponDataTable, ArmorDataTable, JewelryDataTable, DiceDataTable
* �������� ������� ������ - ����� �������� �� ��� ������� � ������� ���.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROWSEPROJECT_API ULootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Method of Spawning Loot"), Category = "Loot System")
	ELootType LootType;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Custom Loot List", EditCondition = "LootType == ELootType::ELT_Custom"), Category = "Loot System")
	TArray<FLootRow> CustomLootList;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Loot Data Table", EditCondition = "LootType == ELootType::ELT_LootDataTable"), Category = "Loot System")
	FDataTableRowHandle LootDataTableRows;



public:

	// Sets default values for this component's properties
	ULootComponent();

	// ����������������� ������� ��� ������ ����
	UFUNCTION(BlueprintCallable)
	void SpawnLoot(FTransform SpawnTransform);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// ����������������� ������� ��� ������ ����
	void SpawnLootFromLootTable(FTransform SpawnTransform);

	// ������� ��� ������ ���������� ����
	void SpawnCustomLoot(FTransform SpawnTransform);

	// ������� ��������� ����� ������ �� ������� ������������� ����
	template<typename T>
	static T* CastFindStruct(TObjectPtr<const UDataTable>, FName RowName);

	// ������� ������� ������� � ��������� ������ ������ ��������
	AWorldItem* SpawnItemAtWorld(UBasicItem*& ItemObject, FItemDataRow* Data, FTransform SpawnTransform,
		const wchar_t* TextOnSuccess = TEXT("Success on Spawn Item to World"),
		const wchar_t* TextOnError = TEXT("Error on Spawn"));

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
