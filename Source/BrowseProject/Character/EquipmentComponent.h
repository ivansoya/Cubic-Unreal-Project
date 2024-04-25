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

	// �������� ���������� ���������
	UPROPERTY(VisibleAnywhere, Category = "Equipment", meta = (DisplayName = "Equipment List", AllowPrivateAccess = "true"))
	TMap<ESlotType, FEquipmentSlot> _EquipmentSlots;

	// ������ ���������� ������� � ���������
	UPROPERTY(VisibleAnywhere, Category = "Equipment", meta = (DisplayName = "Dice List", AllowPrivateAccess = "true"))
	TMap<EDice, UDice*> _DiceList;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// ������������� ������� � ����
	/// </summary>
	/// <param name="Slot">����</param>
	/// <param name="Item">������� ����������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	bool SetItemInSlot(ESlotType Slot, UEquipmentItem* Item);

	/// <summary>
	/// ������� ������� �� �����
	/// </summary>
	/// <param name="Slot">��� �����</param>
	/// <returns>��������� �� ��������� �������</returns>
	UFUNCTION(BlueprintCallable)
	UEquipmentItem* WithdrawItemFromSlot(ESlotType Slot);

	/// <summary>
	/// ���������� ����� �� ������� ���� ������ ����������
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	TMap<ESlotType, FEquipmentSlot> GetEquipmentSlotList() const;

	/// <summary>
	/// ���������� ������� �� ����� ���������
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UEquipmentItem* GetEquipmentItemFromList(ESlotType Slot);

	/// <summary>
	/// ������������� ���������� ����� � ����
	/// </summary>
	/// <param name="Slot">����</param>
	/// <param name="Dice">�����</param>
	/// <returns>������ ��� ������� ���������</returns>
	UFUNCTION(BlueprintCallable)
	bool SetDiceInSlot(EDice Slot, UDice* Dice);

	/// <summary>
	/// ���������� ����� �� �����
	/// </summary>
	UFUNCTION(BlueprintCallable)
	UDice* GetDiceFromSlot(EDice Slot) const;

	/// <summary>
	/// ���������� ������ �������
	/// </summary>
	UFUNCTION(BlueprintCallable)
	TMap<EDice, UDice*> GetDiceList() const;

	/// <summary>
	/// ���������� ��������� ����� ����������
	/// </summary>
	/// <param name="Slot">��� �����</param>
	/// <returns>���������, ������ � ���� ������� � ������ �����</returns>
	//UFUNCTION(BlueprintCallable)
	FEquipmentSlot* GetEquipmentSlot(ESlotType Slot);
		
};
