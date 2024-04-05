// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrowseProject/ItemSystem/ItemEnums.h"
#include "EquipmentComponent.generated.h"

class UEquipmentItem;

/// <summary>
/// —труктура дл€ определени€ типа и успешности операций при одевании предметов
/// 
/// OperationText - описание операции
/// IsSuccessfully - успешна€ ли операци€
/// </summary>
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FEquipOperationStatus
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Text of Operation Result"))
	FString OperationText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Result"))
	bool IsSuccessfully;
};

/// <summary>
/// —труктура слотов в экипировки
/// </summary>
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FEquipmentSlot 
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Ref of Item Object"))
	UEquipmentItem* Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "Slot Status"))
	ESlotStatus Status;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROWSEPROJECT_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

private:

	UPROPERTY(VisibleAnywhere, Category = "Equipment", meta = (DisplayName = "Equipment List", AllowPrivateAccess = "true"))
	TMap<ESlotType, FEquipmentSlot> _EquipmentSlots;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	FEquipOperationStatus SetItemInSlot(ESlotType Slot, UEquipmentItem* Item, ESlotStatus Status);

	UFUNCTION(BlueprintCallable)
	UEquipmentItem* WithdrawItemFromSlot(ESlotType Slot);

	UFUNCTION(BlueprintCallable)
	TMap<ESlotType, FEquipmentSlot> GetEquipmentSlots() const;

	UFUNCTION(BlueprintCallable)
	FEquipmentSlot GetEquipmentSlot(ESlotType Slot) const;
		
};
