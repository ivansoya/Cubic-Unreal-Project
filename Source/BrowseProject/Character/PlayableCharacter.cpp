// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "InventoryComponent.h"
#include "EquipmentComponent.h"
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
// Реализация методов интерфейса Equipment
//--------------------------------------

// Функция для одевания предмета на персонажа
bool APlayableCharacter::EquipItemOnCharacter_Implementation(UEquipmentItem* Item, ESlotStatus SlotStatus)
{
	if (Item == nullptr) {
		return false;
	}
	if (_EquipmentComponent->SetItemInSlot(Item->GetItemSlot(), Item, SlotStatus).IsSuccessfully == true) {
		return true;
	}
	else {
		return false;
	}
}

bool APlayableCharacter::SetSkeletalMeshAsCharacterPart_Implementation(USkeletalMesh* SkeletalMesh, ESlotType Slot)
{
	auto t = *_CharacterParts.Find(Slot);
	if (SkeletalMesh) {
		t->SetSkeletalMesh(SkeletalMesh);
		return true;
	}
	return false;
}

//--------------------------------------
// Реализация методов интерфейса Inventory
//--------------------------------------

EStatusOnAdd APlayableCharacter::AddEquipItemToInventory_Implementation(UEquipmentItem* EquipItem)
{
	if (EquipItem) {
		_InventoryComponent->AddEquipItem(EquipItem);
		return EStatusOnAdd::ADDED;
	}
	else {
		return EStatusOnAdd::NULL_ERROR;
	}
}

EStatusOnAdd APlayableCharacter::AddBasicItemToInventory_Implementation(UBasicItem* BasicItem)
{
	return EStatusOnAdd::NULL_ERROR;
}

//-------------------------------------
// 
// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

