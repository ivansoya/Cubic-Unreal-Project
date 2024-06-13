// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BrowseProject/Character/Interfaces/FunctionalityComponents.h"
#include "BrowseProject/Character/Interfaces/Inventory.h"
#include "BrowseProject/Character/Interfaces/Equipment.h"
#include "BrowseProject/Character/Interfaces/Stat.h"
#include "PlayableCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UEquipmentComponent;
class UStatComponent;

UCLASS()
class BROWSEPROJECT_API APlayableCharacter : public ACharacter, public IFunctionalityComponents, public IInventory, public IEquipment, public IStatInterface
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Stat Component", AllowPrivateAccess = "true"))
	TObjectPtr<UStatComponent> _StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Skeletal Meshes", meta = (DisplayName = "Character Parts List", AllowPrivateAccess = "true"))
	TMap<ESlotType, USkeletalMeshComponent*> _CharacterParts;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Spring Arm", AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> _SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Camera Component", AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _CameraComponent;

protected:

	// Делегат, который активируется при надевании предмета
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Equipment Events", meta = (DisplayName = "On Equip Item Signature", AllowPrivateAccess = "true"))
	FOnEquipItemSignature _OnEquipItem;

	// Делегат, который активируется при снятии предмета
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Equipment Events", meta = (DisplayName = "On Withdraw Item Signature", AllowPrivateAccess = "true"))
	FOnWithdrawItemSignature _OnWithdrawItem;

	// Делегат, который активируется при добавлении предмета в инвентарь
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Events", meta = (DisplayName = "On Add Item To Inventory Signature", AllowPrivateAccess = "true"))
	FOnAddItemToInventorySignature _OnAddItemToInventory;

	// Делегат, который активируется при удалении предмета из инвентаря
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Events", meta = (DisplayName = "On Remove Item From Inventory Signature", AllowPrivateAccess = "true"))
	FOnRemoveItemFromInventorySignature _OnRemoveItemFromInventory;

	// Делегат, который активируется при добавлении кубика в карман
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Events", meta = (DisplayName = "On Put Dice In Pocket", AllowPrivateAccess = "true"))
	FOnPutMagicDiceInPocketSignature _OnPutMagicDiceInPocket;

	// Делегат, который активируется при удалении кубика из кармана
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Events", meta = (DisplayName = "On Take Off Dice From Pocket", AllowPrivateAccess = "true"))
	FOnTakeOffDiceFromPocketSignature _OnTakeOffDiceFromPocket;

	//=====================================================
	//	Делегаты IStat
	//=====================================================
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Stat Events", meta = (DisplayName = "On Health Changed", AllowPrivateAccess = "true"))
	FOnHealthChangedSignature _OnHealthChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Stat Events", meta = (DisplayName = "On Mana Changed", AllowPrivateAccess = "true"))
	FOnManaChangedSignature _OnManaChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Stat Events", meta = (DisplayName = "On Stamina Changed", AllowPrivateAccess = "true"))
	FOnStaminaChangedSignature _OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Stat Events", meta = (DisplayName = "On Durability Changed", AllowPrivateAccess = "true"))
	FOnDurabilityChangedSignature _OnDurabilityChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Stat Events", meta = (DisplayName = "On Death", AllowPrivateAccess = "true"))
	FOnDeathSignature _OnDeath;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Stat Events", meta = (DisplayName = "On Healed", AllowPrivateAccess = "true"))
	FOnActorHealedSignature _OnHealed;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Health", AllowPrivateAccess = "true"))
	int32 _Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Mana", AllowPrivateAccess = "true"))
	int32 _Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Stamina", AllowPrivateAccess = "true"))
	int32 _Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Durability", AllowPrivateAccess = "true"))
	int32 _Durability;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void PreRegisterAllComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//===============================================================================
// Объявление методов интерфейса IStat
//===============================================================================
public:

	/// <summary>
	/// Ролит значение атаки, которое определяет, пробьет ли броню данная атака или нет
	/// </summary>
	/// <param name="Target">Цель атаки</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	int32 RollAttackToEnemy(AActor* Target, const UElementalDamageType* DamageType);

	/// <summary>
	/// Наносит урон цели. 
	/// Урон считается по формуле через ролл Damage Dice. Определяет, будет ли критический урон у атаки или нет
	/// </summary>
	/// <param name="Target">Цель атаки</param>
	/// <param name="DamageType">Тип урона</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	int32 DealDamageToTarget(AActor* Target, const UElementalDamageType* DamageType);

	/// <summary>
	/// Функция, которая передает урон по персонажу
	/// </summary>
	/// <param name="Damage">Количество урона</param>
	/// <param name="DamageType">Типа урона</param>
	/// <param name="IsCrit">Является ли атака критической</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	int32 TakeDamageFromEnemy(int32 Damage, const UElementalDamageType* DamageType, bool IsCrit);

	/// <summary>
	/// Функция, которая передает лечение для персонажа
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	int32 TakeHeal(int32 HealAmount);

	/// <summary>
	/// Изменяет значение характеристик у персонажа
	/// Тип определяет, с каким видом характеристики взаимодействует функция: c базовым или добавочным
	/// Внимание! General не относится к данной функции!
	/// </summary>
	/// <param name="Value">Значение характеристики</param>
	/// <param name="Key">Ключ характеристики</param>
	/// <param name="Type">Тип</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	void ChangeCharacterStatValue(int32 Value, EStatKey Key, EStatTypeRetuned Type);

	/// <summary>
	/// Изменяет значение элементальных бонусов у персонажа
	/// Тип определяет, с каким видом характеристики взаимодействует функция: c базовым или добавочным
	/// Внимание! General не относится к данной функции!
	/// </summary>
	/// <param name="Value">Значение характеристики</param>
	/// <param name="Element">Элемент</param>
	/// <param name="Type">Тип</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	void ChangeElementalValue(int32 Value, UElementalDamageType* Element, EStatElementalType Type);

//===============================================================================
// Объявление методов интерфейса IEquipment
//===============================================================================
public:

	/// <summary>
	/// Функция для одевания предмета на персонажа
	/// </summary>
	/// <param name="Item">Указатель на одеваемый предмет</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool EquipItemOnCharacter(UEquipmentItem* Item, ESlotType Slot);

	/// <summary>
	/// Функция для смены модели части персонажа
	/// </summary>
	/// <param name="SkeletalMesh">Скелетированная Модель</param>
	/// <param name="Slot">Часть, которая будет заменена</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetSkeletalMeshAsCharacterPart(USkeletalMesh* SkeletalMesh, ESlotType Slot);

	/// <summary>
	/// Меняет текущую модель части тела на дефолтную 
	/// Модель выбирается из заготовленного списка, который формируется в редакторе игры
	/// </summary>
	/// <param name="Slot">Слот модели</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetBasicSkeletalMeshAtSlot(ESlotType Slot);

	/// <summary>
	/// Функция снимает предмет из слота экипировки
	/// </summary>
	/// <param name="Slot">Слот персонажа</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool WithdrawItemFromCharacterSlot(ESlotType Slot);

	/// <summary>
	/// Возвращает указатель на структуру слота
	/// </summary>
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	virtual FEquipmentSlot* GetSlotStructure(ESlotType Slot) override;

	/// <summary>
	/// Устанавливает новый статус слота
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool ChangeSlotStatus(ESlotType Slot, ESlotStatus Status);

	/// <summary>
	/// Возвращает дефолтный статус слота экипировки
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool ReturnDefaultSlotStatus(ESlotType Slot, ESlotStatus Status);

	/// <summary>
	/// Возвращает магический кубик из слота кармана
	/// </summary>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UDice* GetDiceFromSlot(EDice Slot);

	/// <summary>
	/// Кладет магический кубик в переданный слот кармана
	/// </summary>
	/// <param name="Slot">Слот</param>
	/// <param name="Dice">Кубик</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool PutDiceInPocket(EDice Slot, UDice* Dice);

	/// <summary>
	/// Выкладывает кубик из кармана соответствующего слота
	/// </summary>
	/// <param name="Slot">Слот</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool TakeOffDiceFromPocket(EDice Slot);

	// Геттеры делегатов
	virtual FOnEquipItemSignature& GetOnEquipItemSignature() override;
	virtual FOnWithdrawItemSignature& GetOnWithdrawItemSignature() override;
	virtual FOnPutMagicDiceInPocketSignature& GetOnPutMagicDiceInPocketSignature() override;
	virtual FOnTakeOffDiceFromPocketSignature& GetOnTakeOffDiceFromPocketSignature() override;

//===============================================================================
// Объявление методов интерфейса Inventory
//===============================================================================
public:

	/// <summary>
	/// Добавление предмета в список экипировки
	/// </summary>
	/// <param name="EquipItem">Предмет экипировки</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EStatusOnAdd AddEquipItemToInventory(UEquipmentItem* EquipItem);

	/// <summary>
	/// Удаляет экипируемый предмет из инвентаря
	/// </summary>
	/// <param name="EquipmentItem">Предмет, который нужно удалить</param>
	/// <returns>Удаляемый предмет</returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveEquipItemFromInventoryByFind(UEquipmentItem* RemoveItem);

	/// <summary>
	/// Добавление предмета в список обычных предметов
	/// </summary>
	/// <param name="BasicItem">Обыкновенный предмет</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EStatusOnAdd AddBasicItemToInventory(UBasicItem* BasicItem);

	/// <summary>
	/// Функция возврата делегата экипировки предметов 
	/// </summary>
	/// <returns></returns>
	virtual FOnAddItemToInventorySignature& GetOnAddItemToInventorySignature() override;

	/// <summary>
	/// Функция возврата делегата снятия предметов 
	/// </summary>
	/// <returns></returns>
	virtual FOnRemoveItemFromInventorySignature& GetOnRemoveItemFromInventorySignature() override;


//===============================================================================
// Объявление методов интерфейса Functionality Components
//===============================================================================
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInventoryComponent* GetInventoryComponent();

private:

	// Компонент сцены, на который крепятся части тела актера
	TObjectPtr<USceneComponent> _CharacterPartsSceneComponent;

	// Словарь с именами моделей частей тела актера
	TMap<ESlotType, FName> _AllTypeMeshes;

	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (DisplayName = "Default Character Parts", AllowPrivateAccess = "true"))
	TMap<ESlotType, USkeletalMesh*> _DefaultSkeletalParts;
};
