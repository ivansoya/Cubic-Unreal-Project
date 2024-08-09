// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrowseProject/General/Items/System/ItemEnums.h"
#include "EquipmentComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROWSEPROJECT_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

private:

	// Перечень экипировки персонажа
	//UPROPERTY(VisibleAnywhere, Category = "Equipment", meta = (DisplayName = "Equipment List", AllowPrivateAccess = "true"))
	TMap<ESlotType, const UEquipmentItem*> _EquipmentSlots;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Устанавливает предмет в слот
	/// </summary>
	/// <param name="Slot">Слот</param>
	/// <param name="Item">Предмет экипировки</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	bool SetItemInSlot(ESlotType Slot, const UEquipmentItem* Item);

	/// <summary>
	/// Удаляет предмет из слота
	/// </summary>
	/// <param name="Slot">Тип слота</param>
	/// <returns>Указатель на удаляемый предмет</returns>
	UFUNCTION(BlueprintCallable)
	const UEquipmentItem* WithdrawItemFromSlot(ESlotType Slot);

	/// <summary>
	/// Возвращает карту со списком всех слотов экипировки
	/// </summary>
	/// <returns></returns>
	//UFUNCTION(BlueprintCallable)
	const TMap<ESlotType, const UEquipmentItem*>& GetEquipmentList() const;

	/// <summary>
	/// Возвращает предмет из слота инвентаря
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const UEquipmentItem* GetEquipmentItemFromList(ESlotType Slot) const;

	/// <summary>
	/// Возвращает объект кубика из слота экипировки
	/// </summary>
	/// <param name="Slot">Слот экипировки. Возможные значения: ATTACK_DICE, DAMAGE_DICE, TRIAL_DICE
	/// </param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	const UDice* GetDiceFromSlot(ESlotType Slot) const;

	/// <summary>
	/// Возвращает список кубиков
	/// </summary>
	//UFUNCTION(BlueprintCallable)
	const TMap<ESlotType, const UDice*> GetDiceList() const;
		
};
