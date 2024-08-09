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

	// �������� ���������� ���������
	//UPROPERTY(VisibleAnywhere, Category = "Equipment", meta = (DisplayName = "Equipment List", AllowPrivateAccess = "true"))
	TMap<ESlotType, const UEquipmentItem*> _EquipmentSlots;

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
	bool SetItemInSlot(ESlotType Slot, const UEquipmentItem* Item);

	/// <summary>
	/// ������� ������� �� �����
	/// </summary>
	/// <param name="Slot">��� �����</param>
	/// <returns>��������� �� ��������� �������</returns>
	UFUNCTION(BlueprintCallable)
	const UEquipmentItem* WithdrawItemFromSlot(ESlotType Slot);

	/// <summary>
	/// ���������� ����� �� ������� ���� ������ ����������
	/// </summary>
	/// <returns></returns>
	//UFUNCTION(BlueprintCallable)
	const TMap<ESlotType, const UEquipmentItem*>& GetEquipmentList() const;

	/// <summary>
	/// ���������� ������� �� ����� ���������
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const UEquipmentItem* GetEquipmentItemFromList(ESlotType Slot) const;

	/// <summary>
	/// ���������� ������ ������ �� ����� ����������
	/// </summary>
	/// <param name="Slot">���� ����������. ��������� ��������: ATTACK_DICE, DAMAGE_DICE, TRIAL_DICE
	/// </param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	const UDice* GetDiceFromSlot(ESlotType Slot) const;

	/// <summary>
	/// ���������� ������ �������
	/// </summary>
	//UFUNCTION(BlueprintCallable)
	const TMap<ESlotType, const UDice*> GetDiceList() const;
		
};
