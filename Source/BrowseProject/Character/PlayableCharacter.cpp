// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "InventoryComponent.h"
#include "BrowseProject/ItemSystem/ItemEnums.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->DestroyComponent();
	GetMesh()->SetActive(false);

	TObjectPtr<USceneComponent> CharacterParts = CreateDefaultSubobject<USceneComponent>("List of Character Parts");
	CharacterParts->SetRelativeTransform(FTransform(FRotator(), FVector3d(0, 0, -GetDefaultHalfHeight())));
	CharacterParts->SetupAttachment(RootComponent);

	_SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	_SpringArm->SetWorldRotation(FRotator(-50, 0, 0));
	_SpringArm->TargetArmLength = 1400;
	_SpringArm->bInheritPitch = true;
	_SpringArm->bInheritRoll = true;
	_SpringArm->bInheritYaw = true;
	_SpringArm->SetupAttachment(RootComponent);

	_CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	_CameraComponent->ProjectionMode = ECameraProjectionMode::Type::Perspective;
	_CameraComponent->FieldOfView = 55.0;
	_CameraComponent->SetupAttachment(_SpringArm);

	TMap<ESlotType, FName> AllTypeMeshes = {
		{ESlotType::EST_Head, "Head"},
		{ESlotType::EST_Body, "Body"},
		{ESlotType::EST_Hands, "Hands"},
		{ESlotType::EST_Legs, "Legs"},
		{ESlotType::EST_Feet, "Feet"},
	};

	for (TPair<ESlotType, FName> Slot : AllTypeMeshes) {
		TObjectPtr<USkeletalMeshComponent> SK_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(Slot.Value);
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

			SK_Mesh->SetupAttachment(CharacterParts);
			_CharacterParts.Add(TPair<ESlotType, TObjectPtr<USkeletalMeshComponent>>(Slot.Key, SK_Mesh));
		}
	}

	_InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory Component");
	if (_InventoryComponent) {
		
	}

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

