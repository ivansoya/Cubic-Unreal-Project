// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "InventoryComponent.h"
#include "EquipmentComponent.h"
#include "StatComponent.h"
#include "BrowseProject/ItemSystem/ItemObjects.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->DestroyComponent();
	GetMesh()->SetActive(false);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	_CharacterPartsSceneComponent = CreateDefaultSubobject<USceneComponent>("List of Character Parts");
	_CharacterPartsSceneComponent->SetRelativeTransform(FTransform(FRotator(), FVector3d(0, 0, -GetDefaultHalfHeight())));
	_CharacterPartsSceneComponent->SetupAttachment(RootComponent);

	_SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	_SpringArm->SetWorldRotation(FRotator(-50, 0, 0));
	_SpringArm->TargetArmLength = 1400;
	_SpringArm->bUsePawnControlRotation = false;
	_SpringArm->bInheritPitch = false;
	_SpringArm->bInheritRoll = false;
	_SpringArm->bInheritYaw = false;
	_SpringArm->SetupAttachment(RootComponent);

	_CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	_CameraComponent->ProjectionMode = ECameraProjectionMode::Type::Perspective;
	_CameraComponent->FieldOfView = 55.0;
	_CameraComponent->SetupAttachment(_SpringArm);

	_AllTypeMeshes = {
		{ESlotType::HEAD, "Head"},
		{ESlotType::BODY, "Body"},
		{ESlotType::HANDS, "Hands"},
		{ESlotType::LEGS, "Legs"},
		{ESlotType::FEET, "Feet"},
	};

	for (TPair<ESlotType, FName> Slot : _AllTypeMeshes) {
		USkeletalMeshComponent* SK_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(Slot.Value);
		if (SK_Mesh)
		{
			SK_Mesh->AlwaysLoadOnClient = true;
			SK_Mesh->AlwaysLoadOnServer = true;
			SK_Mesh->bOwnerNoSee = false;
			SK_Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
			SK_Mesh->bCastDynamicShadow = true;
			SK_Mesh->bAffectDynamicIndirectLighting = true;
			SK_Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
			static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
			SK_Mesh->SetCollisionProfileName(MeshCollisionProfileName);
			SK_Mesh->SetGenerateOverlapEvents(false);
			SK_Mesh->SetCanEverAffectNavigation(false);
			SK_Mesh->SetRelativeRotation(FRotator(0, -90, 0));

			SK_Mesh->SetupAttachment(_CharacterPartsSceneComponent);
			_CharacterParts.Add(TPair<ESlotType, USkeletalMeshComponent*>(Slot.Key, SK_Mesh));
		}
	}

	_InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory Component");
	if (_InventoryComponent) {
		
	}

	_EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>("Equipment Component");
	if (_EquipmentComponent) {
		
	}

	_StatComponent = CreateDefaultSubobject<UStatComponent>("Stat Component");
	if (_StatComponent) {
		
	}
}

void APlayableCharacter::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();
}

void APlayableCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

//--------------------------------------
// Реализация методов интерфейса Functionality Components
//--------------------------------------

// Функция, возвращающая Inventory Component
UInventoryComponent* APlayableCharacter::GetInventoryComponent_Implementation()
{
	return _InventoryComponent;
}

//-------------------------------------

//--------------------------------------
// Реализация методов интерфейса IStat
//--------------------------------------

int32 APlayableCharacter::RollAttackToEnemy_Implementation(AActor* Target, const UElementalDamageType* DamageType)
{
	return 10;
}

int32 APlayableCharacter::DealDamageToTarget_Implementation(AActor* Target, const UElementalDamageType* DamageType)
{
	return 10;
}

int32 APlayableCharacter::TakeDamageFromEnemy_Implementation(int32 Damage, const UElementalDamageType* DamageType, bool IsCrit)
{
	_Health = _Health - Damage;
	if (_Health < 0) {
		_Health = 0;
		_OnDeath.Broadcast();
	}
	_OnHealthChanged.Broadcast(_Health, _StatComponent->GetStatValue(EStatKey::HEALTH, EStatTypeRetuned::GENERAL));
	return _Health;
}

int32 APlayableCharacter::TakeHeal_Implementation(int32 HealAmount)
{
	_OnHealed.Broadcast(HealAmount);
	_Health = _Health + HealAmount;
	int32 MaxHealth = _StatComponent->GetStatValue(EStatKey::HEALTH, EStatTypeRetuned::GENERAL);
	if (_Health > MaxHealth) {
		_Health = MaxHealth;
	}
	_OnHealthChanged.Broadcast(_Health, MaxHealth);
	return _Health;
}
//-------------------------------------

//--------------------------------------
// Реализация методов интерфейса Equipment
//--------------------------------------

// Функция для одевания предмета на персонажа
bool APlayableCharacter::EquipItemOnCharacter_Implementation(UEquipmentItem* Item, ESlotType Slot)
{
	if (Item == nullptr) {
		return false;
	}
	auto slot_t = _EquipmentComponent->GetEquipmentSlot(Slot);
	if (slot_t) {
		// Проверяем заблокирован ли стол
		if ((*slot_t).Status <= ESlotStatus::BLOCKED) {
			return false;
		}
		// Проверяем есть ли предмет в слоте, в который мы хотим поставить предмет
		if ((*slot_t).Item) {
			// Убираем предмет из слота
			(*slot_t).Item->WithdrawFromCharacter(this);
		}
		// Устанавливаем предмет в слот экипировки персонажа
		if (_EquipmentComponent->SetItemInSlot(Slot, Item)) {
			// Вызываем событие, что предмет одет в слот
			_OnEquipItem.Broadcast(*slot_t, Slot);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool APlayableCharacter::SetSkeletalMeshAsCharacterPart_Implementation(USkeletalMesh* SkeletalMesh, ESlotType Slot)
{
	auto t = _CharacterParts.Find(Slot);
	if (SkeletalMesh && t) {
		(*t)->SetSkeletalMesh(SkeletalMesh);
		return true;
	}
	return false;
}

bool APlayableCharacter::SetBasicSkeletalMeshAtSlot_Implementation(ESlotType Slot)
{
	auto mesh = _DefaultSkeletalParts.Find(Slot);
	if (mesh) {
		auto t = _CharacterParts.Find(Slot);
		if (*t != nullptr) {
			(*t)->SetSkeletalMesh((*mesh));
			return true;
		}
	}
	return false;
}

bool APlayableCharacter::WithdrawItemFromCharacterSlot_Implementation(ESlotType Slot)
{
	auto item_t = _EquipmentComponent->WithdrawItemFromSlot(Slot);
	if (item_t == nullptr) {
		return false;
	}
	else {
		_OnWithdrawItem.Broadcast(*_EquipmentComponent->GetEquipmentSlot(Slot), Slot);
		return false;
	}
}

FEquipmentSlot* APlayableCharacter::GetSlotStructure(ESlotType Slot)
{
	return _EquipmentComponent->GetEquipmentSlot(Slot);
}

bool APlayableCharacter::ChangeSlotStatus_Implementation(ESlotType Slot, ESlotStatus Status)
{
	auto slot_t = _EquipmentComponent->GetEquipmentSlot(Slot);
	if (slot_t == nullptr) {
		return false;
	}

	(*slot_t).Status = Status;
	return true;
}

bool APlayableCharacter::ReturnDefaultSlotStatus_Implementation(ESlotType Slot, ESlotStatus Status)
{
	auto slot_t = _EquipmentComponent->GetEquipmentSlot(Slot);
	if (slot_t == nullptr) {
		return false;
	}

	(*slot_t).Status = (*slot_t).DefaultStatus;
	return true;
}

UDice* APlayableCharacter::GetDiceFromSlot_Implementation(EDice Slot)
{
	return _EquipmentComponent->GetDiceFromSlot(Slot);
}

bool APlayableCharacter::PutDiceInPocket_Implementation(EDice Slot, UDice* Dice)
{
	if (Dice == nullptr) {
		return false;
	}
	if (_EquipmentComponent->SetDiceInSlot(Slot, Dice) == true) {
		_OnPutMagicDiceInPocket.Broadcast(Dice, Slot);
		return true;
	}
	return false;
}

bool APlayableCharacter::TakeOffDiceFromPocket_Implementation(EDice Slot)
{
	if (_EquipmentComponent->SetDiceInSlot(Slot, nullptr) == true) {
		_OnTakeOffDiceFromPocket.Broadcast(nullptr, Slot);
		return true;
	}
	else return false;
}

FOnEquipItemSignature& APlayableCharacter::GetOnEquipItemSignature()
{
	return _OnEquipItem;
}

FOnWithdrawItemSignature& APlayableCharacter::GetOnWithdrawItemSignature()
{
	return _OnWithdrawItem;
}

FOnPutMagicDiceInPocketSignature& APlayableCharacter::GetOnPutMagicDiceInPocketSignature()
{
	return _OnPutMagicDiceInPocket;
}

FOnTakeOffDiceFromPocketSignature& APlayableCharacter::GetOnTakeOffDiceFromPocketSignature()
{
	return _OnTakeOffDiceFromPocket;
}

//--------------------------------------
// Реализация методов интерфейса Inventory
//--------------------------------------

void APlayableCharacter::RemoveEquipItemFromInventoryByFind_Implementation(UEquipmentItem* RemoveItem)
{
	if (_InventoryComponent->RemoveEquipmentItemFromListByFind(RemoveItem) == true) {
		_OnRemoveItemFromInventory.Broadcast(RemoveItem);
	}
}

EStatusOnAdd APlayableCharacter::AddEquipItemToInventory_Implementation(UEquipmentItem* EquipItem)
{
	if (EquipItem) {
		_InventoryComponent->AddEquipItemAtList(EquipItem);
		_OnAddItemToInventory.Broadcast(EquipItem);
		return EStatusOnAdd::ADDED;
	}
	else {
		return EStatusOnAdd::NULL_ERROR;
	}
}

EStatusOnAdd APlayableCharacter::AddBasicItemToInventory_Implementation(UBasicItem* BasicItem)
{
	_OnAddItemToInventory.Broadcast(BasicItem);
	return EStatusOnAdd::NULL_ERROR;
}

FOnAddItemToInventorySignature& APlayableCharacter::GetOnAddItemToInventorySignature()
{
	return _OnAddItemToInventory;
}

FOnRemoveItemFromInventorySignature& APlayableCharacter::GetOnRemoveItemFromInventorySignature()
{
	return _OnRemoveItemFromInventory;
}

//-------------------------------------
// 
// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	_Health = _StatComponent->GetStatValue(EStatKey::HEALTH, EStatTypeRetuned::GENERAL);
	_Mana = _StatComponent->GetStatValue(EStatKey::MANA, EStatTypeRetuned::GENERAL);
	_Stamina = _StatComponent->GetStatValue(EStatKey::HEALTH, EStatTypeRetuned::GENERAL);
	_Durability = _StatComponent->GetStatValue(EStatKey::HEALTH, EStatTypeRetuned::GENERAL);

	// Нужно для обновления всех виджетов
	_OnHealthChanged.Broadcast(_Health, _Health);
	_OnManaChanged.Broadcast(_Mana, _Mana);
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

