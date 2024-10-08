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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Skeletal Meshes", meta = (DisplayName = "Left Weapon", AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> _LeftWeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Skeletal Meshes", meta = (DisplayName = "Right Weapon", AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> _RightWeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Spring Arm", AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> _SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Components", meta = (DisplayName = "Camera Component", AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _CameraComponent;

protected:

	// �������, ������� ������������ ��� ��������� ��������
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Equipment Events", meta = (DisplayName = "On Equip Item Signature", AllowPrivateAccess = "true"))
	FOnEquipItemSignature _OnEquipItem;

	// �������, ������� ������������ ��� ������ ��������
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Equipment Events", meta = (DisplayName = "On Withdraw Item Signature", AllowPrivateAccess = "true"))
	FOnWithdrawItemSignature _OnWithdrawItem;

	// �������, ������� ������������ ��� ��������� ���������
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Events", meta = (DisplayName = "On Inventory Changed Signature", AllowPrivateAccess = "true"))
	FOnInventoryChangedSignature _OnInventoryChanged;

	//=====================================================
	//	�������� IStat
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

//===============================================================================
// �������� ����� ��� ����������
//===============================================================================
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Health", AllowPrivateAccess = "true"))
	int32 _Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Mana", AllowPrivateAccess = "true"))
	int32 _Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Stamina", AllowPrivateAccess = "true"))
	int32 _Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Durability", AllowPrivateAccess = "true"))
	int32 _Durability;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stats", meta = (DisplayName = "Weapon Stances", AllowPrivateAccess = "true"))
	TArray<EWeaponType> _WeaponStances;

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
// ���������� ������� ���������� IStat
//===============================================================================
public:

	/// <summary>
	/// ����� �������� �����, ������� ����������, ������� �� ����� ������ ����� ��� ���
	/// </summary>
	/// <param name="Target">���� �����</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	int32 RollAttackToEnemy(AActor* Target, const UElementalDamageType* DamageType);

	/// <summary>
	/// ������� ���� ����. 
	/// ���� ��������� �� ������� ����� ���� Damage Dice. ����������, ����� �� ����������� ���� � ����� ��� ���
	/// </summary>
	/// <param name="Target">���� �����</param>
	/// <param name="DamageType">��� �����</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	int32 DealDamageToTarget(AActor* Target, const UElementalDamageType* DamageType);

	/// <summary>
	/// �������, ������� �������� ���� �� ���������
	/// </summary>
	/// <param name="Damage">���������� �����</param>
	/// <param name="DamageType">���� �����</param>
	/// <param name="IsCrit">�������� �� ����� �����������</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	int32 TakeDamageFromEnemy(int32 Damage, const UElementalDamageType* DamageType, bool IsCrit);

	/// <summary>
	/// �������, ������� �������� ������� ��� ���������
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	int32 TakeHeal(int32 HealAmount);

	/// <summary>
	/// �������� �������� ������������� � ���������
	/// ��� ����������, � ����� ����� �������������� ��������������� �������: c ������� ��� ����������
	/// ��������! General �� ��������� � ������ �������!
	/// </summary>
	/// <param name="Value">�������� ��������������</param>
	/// <param name="Key">���� ��������������</param>
	/// <param name="Type">���</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	void ChangeCharacterStatValue(int32 Value, EStatKey Key, EStatTypeRetuned Type);

	/// <summary>
	/// �������� �������� ������������� ������� � ���������
	/// ��� ����������, � ����� ����� �������������� ��������������� �������: c ������� ��� ����������
	/// ��������! General �� ��������� � ������ �������!
	/// </summary>
	/// <param name="Value">�������� ��������������</param>
	/// <param name="Element">�������</param>
	/// <param name="Type">���</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dice Project|Playable Character")
	void ChangeElementalValue(int32 Value, UElementalDamageType* Element, EStatElementalType Type);

//===============================================================================
// ���������� ������� ���������� IEquipment
//===============================================================================
public:

	/// <summary>
	/// ������� ��� �������� �������� �� ���������
	/// </summary>
	/// <param name="Item">��������� �� ��������� �������</param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool EquipItemOnCharacter(const UEquipmentItem* Item, ESlotType Slot);

	/// <summary>
	/// ������� ��� ����� ������ ����� ���������
	/// </summary>
	/// <param name="SkeletalMesh">��������������� ������</param>
	/// <param name="Slot">�����, ������� ����� ��������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetSkeletalMeshAsCharacterPart(USkeletalMesh* SkeletalMesh, ESlotType Slot);

	/// <summary>
	/// ������ ������� ������ ����� ���� �� ��������� 
	/// ������ ���������� �� �������������� ������, ������� ����������� � ��������� ����
	/// </summary>
	/// <param name="Slot">���� ������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetBasicSkeletalMeshAtSlot(ESlotType Slot);

	/// <summary>
	/// ������� ������� ������� �� ����� ����������
	/// </summary>
	/// <param name="Slot">���� ���������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool WithdrawItemFromCharacterSlot(ESlotType Slot);

	/// <summary>
	/// A function that sets the weapon mesh to the specified socket
	/// </summary>
	/// <param name="WeaponMesh">:: Mesh of Equipped weapon</param>
	/// <param name="ArmedWeaponSocket">:: Socket where mesh will be displayed when the player is armed</param>
	/// <param name="UnarmedWeaponSocket">:: Socket where mesh will be displayed when the player is unarmed</param>
	/// <param name="IsRight">:: true = right weapon mesh; false = left weapon mesh</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetWeaponMeshAtSocket(UStaticMesh* WeaponMesh, const FName& WeaponSocket, bool IsRight);

	// ������� ���������
	virtual FOnEquipItemSignature& GetOnEquipItemSignature() override;
	virtual FOnWithdrawItemSignature& GetOnWithdrawItemSignature() override;

//===============================================================================
// ���������� ������� ���������� Inventory
//===============================================================================
public:

	/// <summary>
	/// ���������� �������� � ������ ����������
	/// </summary>
	/// <param name="EquipItem">������� ����������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EStatusOnAdd AddEquipItemToInventory(const UEquipmentItem* EquipItem);

	/// <summary>
	/// ������� ����������� ������� �� ���������
	/// </summary>
	/// <param name="EquipmentItem">�������, ������� ����� �������</param>
	/// <returns>��������� �������</returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveEquipItemFromInventoryByFind(const UEquipmentItem* RemoveItem);

	/// <summary>
	/// ���������� �������� � ������ ������� ���������
	/// </summary>
	/// <param name="BasicItem">������������ �������</param>
	/// <returns></returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EStatusOnAdd AddBasicItemToInventory(const UBasicItem* BasicItem);

	/// <summary>
	/// ������� �������� �������� ��������� ���������
	/// </summary>
	/// <returns></returns>
	virtual FOnInventoryChangedSignature& GetOnAddItemToInventorySignature() override;


//===============================================================================
// ���������� ������� ���������� Functionality Components
//===============================================================================
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInventoryComponent* GetInventoryComponent();

private:

	// ��������� �����, �� ������� �������� ����� ���� ������
	TObjectPtr<USceneComponent> _CharacterPartsSceneComponent;

	// ������� � ������� ������� ������ ���� ������
	TMap<ESlotType, FName> _AllTypeMeshes;

	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (DisplayName = "Default Character Parts", AllowPrivateAccess = "true"))
	TMap<ESlotType, USkeletalMesh*> _DefaultSkeletalParts;
};
