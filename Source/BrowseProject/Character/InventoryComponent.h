// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemTag;
class UItemObject;
class UBasicItem;
class UEquipmentItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisplayItemsSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideItemsSignature);

USTRUCT(BlueprintType)
struct FBasicItemSlotInv {

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBasicItem* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Count;
};

USTRUCT(BlueprintType)
struct FEquipItemSlotInv {
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UEquipmentItem* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isEquipped;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) 
class BROWSEPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void DisplayItems() const;

	UFUNCTION(BlueprintCallable)
	void HideItems() const;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UItemTag> GetClassOfItemTag();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Tags", meta = (DisplayName = "Class of Item Tag"))
	TSubclassOf<UItemTag> _UsedTypeOfItemTag;

	UItemObject* _CachedItem;

	UPROPERTY(BlueprintAssignable)
	FOnDisplayItemsSignature _OnDisplayItemsDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHideItemsSignature _OnHideItemsDelegate;

private:

	// Key - ID of Items, Value - Item Slot Struct
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (DisplayName = "List of Common Items"))
	TMap<int32, FBasicItemSlotInv> _BasicItemList;

	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (DisplayName = "List of Equip Items"))
	TArray<FEquipItemSlotInv> _EquipmentItemList;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddEquipItem(UEquipmentItem* Item);

	UFUNCTION(BlueprintCallable)
	int32 GetCountOfEquipItems();

	UFUNCTION(BlueprintCallable)
	TArray<FEquipItemSlotInv> GetEquipmentItemList() const;

	FOnDisplayItemsSignature& GetDisplaySignature();

	FOnHideItemsSignature& GetHideSignature();

	
};
