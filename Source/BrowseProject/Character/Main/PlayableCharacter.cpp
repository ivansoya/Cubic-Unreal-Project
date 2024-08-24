// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "BrowseProject/Character/Components/EquipmentComponent.h"
#include "BrowseProject/Character/Components/InventoryComponent.h"
#include "BrowseProject/Character/Components/StatComponent.h"
#include "BrowseProject/General/Items/Objects/ItemObjects.h"
#include "BrowseProject/General/MeshSockets.h"
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

	_WeaponStances = {
		EWeaponType::SWORD_SHIELD,
		EWeaponType::BASTARD,
		EWeaponType::BOW,
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
			FName MeshCollisionProfileName(TEXT("NoCollision"));
			SK_Mesh->SetCollisionProfileName(MeshCollisionProfileName);
			SK_Mesh->SetGenerateOverlapEvents(false);
			SK_Mesh->SetCanEverAffectNavigation(false);
			SK_Mesh->SetRelativeRotation(FRotator(0, -90, 0));

			SK_Mesh->SetupAttachment(_CharacterPartsSceneComponent);
			_CharacterParts.Add(TPair<ESlotType, USkeletalMeshComponent*>(Slot.Key, SK_Mesh));
		}
	}

	// Добавляем компоненты мешей для оружий персонажу
	auto head_t = _CharacterParts[ESlotType::HEAD];
	if (head_t) {
		// Создание оружия в левой руке
		_LeftWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Left Weapon");
		_LeftWeaponMesh->bCastDynamicShadow = true;
		_LeftWeaponMesh->bAffectDynamicIndirectLighting = true;
		_LeftWeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
		_LeftWeaponMesh->SetGenerateOverlapEvents(false);
		_LeftWeaponMesh->SetCanEverAffectNavigation(false);

		// Создание оружия в правой руке
		_RightWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Right Weapon");
		_RightWeaponMesh->bCastDynamicShadow = true;
		_RightWeaponMesh->bAffectDynamicIndirectLighting = true;
		_RightWeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
		_RightWeaponMesh->SetGenerateOverlapEvents(false);
		_RightWeaponMesh->SetCanEverAffectNavigation(false);

		// Привязка оружия в правой руке к дефолтному сокету
		FName RightSocketName = UWeaponSocketNames::GetSocketOptions()[0];
		if (head_t->DoesSocketExist(RightSocketName)) {
			_RightWeaponMesh->SetupAttachment(head_t, RightSocketName);
		}
		else {
			_RightWeaponMesh->SetupAttachment(head_t);
		}

		// Привязка оружия в левой руке к дефолтному сокету
		FName LeftSocketName = UWeaponSocketNames::GetSocketOptions()[1];
		if (head_t->DoesSocketExist(LeftSocketName)) {
			_LeftWeaponMesh->SetupAttachment(head_t, LeftSocketName);
		}
		else {
			_LeftWeaponMesh->SetupAttachment(head_t);
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

void APlayableCharacter::ChangeCharacterStatValue_Implementation(int32 Value, EStatKey Key, EStatTypeRetuned Type)
{
	_StatComponent->AddStatValue(Key, Value, Type);
}

void APlayableCharacter::ChangeElementalValue_Implementation(int32 Value, UElementalDamageType* Element, EStatElementalType Type)
{
	if (Type == EStatElementalType::RESISTANCE) {
		_StatComponent->AddElementalResistanceValue(Element, Value);
	}
	else if (Type == EStatElementalType::DAMAGE_BONUS) {
		_StatComponent->AddExtraElementalDamage(Element, Value);
	}
}
//-------------------------------------

//--------------------------------------
// Реализация методов интерфейса Equipment
//--------------------------------------

// Функция для одевания предмета на персонажа
bool APlayableCharacter::EquipItemOnCharacter_Implementation(const UEquipmentItem* Item, ESlotType Slot)
{
	if (Item == nullptr) {
		return false;
	}
	auto item_in_slot = _EquipmentComponent->GetEquipmentItemFromList(Slot);
	// Есть ли в этом слоте предмет
	if (item_in_slot) {
		// Место для проверки свободны ли слоты в инвентаре
		// Отменяем все примененные характеристики к персонажу
		item_in_slot->AnnulItemStatsFromCharacter(this);
		// Удаляем предмет из инвентаря
		_EquipmentComponent->SetItemInSlot(Slot, nullptr);
		// Возвращаем предмет в инвентарь
		_InventoryComponent->AddEquipItemAtList(item_in_slot);
	}
	// Экипируем предмет в слот
	_EquipmentComponent->SetItemInSlot(Slot, Item);
	// Вызываем событие надевания предмета
	_OnEquipItem.Broadcast(Item, Slot);
	// Удаляем предмет из инвентаря
	_InventoryComponent->RemoveEquipmentItemFromListByFind(Item);
	// Вызываем событие изменение инвентаря
	_OnInventoryChanged.Broadcast();
	return true;
}

// Функция изменения модели части персонажа
bool APlayableCharacter::SetSkeletalMeshAsCharacterPart_Implementation(USkeletalMesh* SkeletalMesh, ESlotType Slot)
{
	// находим нужную часть, на которую надевается доспех
	auto SkMesh_t = _CharacterParts.Find(Slot);
	// Если все найдено
	if (SkeletalMesh && SkMesh_t) {
		// Устанавливает новую модедь
		(*SkMesh_t)->SetSkeletalMesh(SkeletalMesh);
		return true;
	}
	return false;
}

// Функция возврата модели ее базового внешнего вида
bool APlayableCharacter::SetBasicSkeletalMeshAtSlot_Implementation(ESlotType Slot)
{
	// Находим часть, которую необходимо изменить
	auto mesh = _DefaultSkeletalParts.Find(Slot);
	if (mesh) {
		// Находим модель, на которую нужно вернуть базовую внешность найденной части персонажа
		auto t = _CharacterParts.Find(Slot);
		if (*t != nullptr) {
			// Устанавливает базовую модедь
			(*t)->SetSkeletalMesh((*mesh));
			return true;
		}
	}
	return false;
}

// Функция снятия предмета с персонажа
// Данная функция только переносит объекты между компонентами персонажа
bool APlayableCharacter::WithdrawItemFromCharacterSlot_Implementation(ESlotType Slot)
{
	// Пробуем убрать предмет из слота
	auto item_t = _EquipmentComponent->WithdrawItemFromSlot(Slot);
	// Если в слоте не было предмета
	if (item_t == nullptr) {
		// ничего не делаем
		return false;
	}
	// Предмет был в слоте и успешно снят
	else {
		// Вызываем делегат надевания предмета
		_OnWithdrawItem.Broadcast(item_t, Slot);
		//Добавляем предмет в инвентарь
		_InventoryComponent->AddEquipItemAtList(item_t);
		// Вызываем делегат обновления инвентаря
		_OnInventoryChanged.Broadcast();
		return true;
	}
}

bool APlayableCharacter::SetWeaponMeshAtSocket_Implementation(UStaticMesh* WeaponMesh, const FName& WeaponSocket, bool IsRight)
{
	// Определение, с каким компонентом происходит взаимодействие
	UStaticMeshComponent* t_WeaponMeshComponent;
	if (IsRight == true) {
		t_WeaponMeshComponent = _RightWeaponMesh;
	}
	else {
		t_WeaponMeshComponent = _LeftWeaponMesh;
	}
	// Была ли передана модель оружия
	if (WeaponMesh == nullptr) {
		t_WeaponMeshComponent->SetVisibility(false);
		return true;
	}
	auto t_Parent = t_WeaponMeshComponent->GetAttachParent();

	// Изменение модели компонента и сокета, к которому она привязана
	t_WeaponMeshComponent->SetStaticMesh(WeaponMesh);
	t_WeaponMeshComponent->SetVisibility(true);
	// Поиск
	if (t_Parent->DoesSocketExist(WeaponSocket) == true) {
		t_WeaponMeshComponent->AttachToComponent(t_Parent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocket);
		return true;
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, TEXT("Weapon Socket doesn't exist!"));
		//UE_LOG(Debug, Warning, TEXT("Weapon Socket doesn't exist!"));
		return false;
	}
}

FOnEquipItemSignature& APlayableCharacter::GetOnEquipItemSignature()
{
	return _OnEquipItem;
}

FOnWithdrawItemSignature& APlayableCharacter::GetOnWithdrawItemSignature()
{
	return _OnWithdrawItem;
}

//--------------------------------------
// Реализация методов интерфейса Inventory
//--------------------------------------

void APlayableCharacter::RemoveEquipItemFromInventoryByFind_Implementation(const UEquipmentItem* RemoveItem)
{
	if (_InventoryComponent->RemoveEquipmentItemFromListByFind(RemoveItem) == true) {
		_OnInventoryChanged.Broadcast();
	}
}

EStatusOnAdd APlayableCharacter::AddEquipItemToInventory_Implementation(const UEquipmentItem* EquipItem)
{
	if (EquipItem) {
		_InventoryComponent->AddEquipItemAtList(EquipItem);
		_OnInventoryChanged.Broadcast();
		return EStatusOnAdd::ADDED;
	}
	else {
		return EStatusOnAdd::NULL_ERROR;
	}
}

EStatusOnAdd APlayableCharacter::AddBasicItemToInventory_Implementation(const UBasicItem* BasicItem)
{
	_OnInventoryChanged.Broadcast();
	return EStatusOnAdd::NULL_ERROR;
}

FOnInventoryChangedSignature& APlayableCharacter::GetOnAddItemToInventorySignature()
{
	return _OnInventoryChanged;
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

