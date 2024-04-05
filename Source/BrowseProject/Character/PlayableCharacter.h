// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FunctionalityComponentsInterface.h"
#include "InventoryInterface.h"
#include "EquipmentInteface.h"
#include "PlayableCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UEquipmentComponent;

UCLASS()
class BROWSEPROJECT_API APlayableCharacter : public ACharacter, public IFunctionalityComponents, public IInventory, public IEquipment
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayableCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Equipment Component", AllowPrivateAccess = "true"))
	TObjectPtr<UEquipmentComponent> _EquipmentComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Inventory Component", AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> _InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Character Parts List", AllowPrivateAccess = "true"))
	TMap<ESlotType, TObjectPtr<USkeletalMeshComponent>> _CharacterParts;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Spring Arm", AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> _SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Camera Component", AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Объявление методов интерфейса Functionality Components

	// Объявление методов интерфейса IEquipment

	/// <summary>
	/// Функция для одевания предмета на персонажа
	/// </summary>
	/// <param name="Item">Указатель на одеваемый предмет</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool EquipItemOnCharacter(UEquipmentItem* Item, ESlotStatus SlotStatus);

	/// <summary>
	/// Функция для смены модели части персонажа
	/// </summary>
	/// <param name="SkeletalMesh">Скелетированная Модель</param>
	/// <param name="Slot">Часть, которая будет заменена</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetSkeletalMeshAsCharacterPart(USkeletalMesh* SkeletalMesh, ESlotType Slot);

	// Объявление методов интерфейса Inventory
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EStatusOnAdd AddEquipItemToInventory(UEquipmentItem* EquipItem);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EStatusOnAdd AddBasicItemToInventory(UBasicItem* BasicItem);

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInventoryComponent* GetInventoryComponent();
};
