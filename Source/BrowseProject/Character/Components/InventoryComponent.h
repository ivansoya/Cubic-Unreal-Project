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
	const UBasicItem* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Count;
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

	/// <summary>
	/// Список предметов экипировки, которые находятся в инвентаре у персонажа и при этом не одеты на персонажа 
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (DisplayName = "List of Equip Items"))
	TArray<const UEquipmentItem*> _EquipmentItemList;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Добавляет предмет в инвентарь экипировки
	/// </summary>
	/// <param name="Item">Предмет экипировки</param>
	UFUNCTION(BlueprintCallable)
	void AddEquipItemAtList(const UEquipmentItem* Item);

	UFUNCTION(BlueprintCallable)
	int32 GetCountOfEquipItems() const;

	/// <summary>
	/// Выводит список всех предметов экипировки
	/// </summary>
	/// <returns></returns>
	//UFUNCTION(BlueprintCallable)
	const TArray<const UEquipmentItem*>& GetEquipmentItemList() const;

	/// <summary>
	/// Функция возвращает предмет экипировки из списка по номеру.
	/// </summary>
	/// <param name="Num">Номер в списке экипировки</param>
	/// <returns>Указатель на предмет экипировки</returns>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const UEquipmentItem* GetEquipmentItemFromListByIndex(int32 Index) const;

	/// <summary>
	/// Удаляет предмет экипировки из списка по номеру 
	/// </summary>
	/// <returns>Указатель на предмет экипировки</returns>
	const UEquipmentItem* RemoveEquipmentItemFromListByIndex(int32 Index);

	/// <summary>
	/// Удаляет предмет экипировки из списка через поиск предмета
	/// </summary>
	bool RemoveEquipmentItemFromListByFind(const UEquipmentItem* RemoveItem);

	/// <summary>
	/// Возвращает делегат отображение предметов
	/// </summary>
	/// <returns></returns>
	FOnDisplayItemsSignature& GetDisplaySignature();

	/// <summary>
	/// Возвращает делегат скрытия предмета
	/// </summary>
	/// <returns></returns>
	FOnHideItemsSignature& GetHideSignature();
};
