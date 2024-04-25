// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SupportingStructs.h"
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
	UPROPERTY(VisibleAnywhere, Category = "Equipment", meta = (DisplayName = "Equipment List", AllowPrivateAccess = "true"))
	TMap<ESlotType, FEquipmentSlot> _EquipmentSlots;

	// Список магических кубиков у персонажа
	UPROPERTY(VisibleAnywhere, Category = "Equipment", meta = (DisplayName = "Dice List", AllowPrivateAccess = "true"))
	TMap<EDice, UDice*> _DiceList;

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
	bool SetItemInSlot(ESlotType Slot, UEquipmentItem* Item);

	/// <summary>
	/// Удаляет предмет из слота
	/// </summary>
	/// <param name="Slot">Тип слота</param>
	/// <returns>Указатель на удаляемый предмет</returns>
	UFUNCTION(BlueprintCallable)
	UEquipmentItem* WithdrawItemFromSlot(ESlotType Slot);

	/// <summary>
	/// Возвращает карту со списком всех слотов экипировки
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	TMap<ESlotType, FEquipmentSlot> GetEquipmentSlotList() const;

	/// <summary>
	/// Возвращает предмет из слота инвентаря
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEquipmentItem* GetEquipmentItemFromList(ESlotType Slot);

	/// <summary>
	/// Устанавливает магический кубик в слот
	/// </summary>
	/// <param name="Slot">Слот</param>
	/// <param name="Dice">Кубик</param>
	/// <returns>Истина при удачной установке</returns>
	UFUNCTION(BlueprintCallable)
	bool SetDiceInSlot(EDice Slot, UDice* Dice);

	/// <summary>
	/// Возвращает кубик из слота
	/// </summary>
	UFUNCTION(BlueprintCallable)
	UDice* GetDiceFromSlot(EDice Slot) const;

	/// <summary>
	/// Возвращает список кубиков
	/// </summary>
	UFUNCTION(BlueprintCallable)
	TMap<EDice, UDice*> GetDiceList() const;

	/// <summary>
	/// Возвращает структуру слота экипировки
	/// </summary>
	/// <param name="Slot">Тип слота</param>
	/// <returns>Структура, хранит в себе предмет и статус слота</returns>
	//UFUNCTION(BlueprintCallable)
	FEquipmentSlot* GetEquipmentSlot(ESlotType Slot);
		
};
