// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalMeshEnemy.h"
#include "Components/ArrowComponent.h"
#include "BrowseProject/Monster/Components/EnemyStatComponent.h"
#include "BrowseProject/General/Items/Loot/LootComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASkeletalMeshEnemy::ASkeletalMeshEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Default Scene Component");

	_CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
	_CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	_CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	_CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	_CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	_CapsuleComponent->SetCanEverAffectNavigation(false);
	_CapsuleComponent->bDynamicObstacle = true;
	_CapsuleComponent->SetupAttachment(RootComponent);

	_CapsuleComponent->OnBeginCursorOver.AddDynamic(this, &ASkeletalMeshEnemy::BeginCursorOver);
	_CapsuleComponent->OnEndCursorOver.AddDynamic(this, &ASkeletalMeshEnemy::EndCursorOver);

	_SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh Component");
	_SkeletalMeshComponent->SetRelativeLocation(FVector(0, 0, -_CapsuleComponent->GetScaledCapsuleHalfHeight()));
	_SkeletalMeshComponent->SetRelativeRotation(FRotator(0, -90, 0));
	_SkeletalMeshComponent->SetupAttachment(_CapsuleComponent);

#if WITH_EDITORONLY_DATA
	_ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (_ArrowComponent)
	{
		_ArrowComponent->ArrowColor = FColor(150, 200, 255);
		_ArrowComponent->bTreatAsASprite = true;
		_ArrowComponent->SetupAttachment(_CapsuleComponent);
		_ArrowComponent->bIsScreenSizeScaled = true;
		_ArrowComponent->SetSimulatePhysics(false);
	}
#endif // WITH_EDITORONLY_DATA

	_StatComponent = CreateDefaultSubobject<UEnemyStatComponent>("Monster Stat Component");

	_LootComponent = CreateDefaultSubobject<ULootComponent>("Loot Component");
}

void ASkeletalMeshEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ASkeletalMeshEnemy::BeginPlay()
{
	Super::BeginPlay();
	// Проверяем есть DataTable
	//if (_EnemyData.DataTable) {
	//	// Проверяем строчку таблицы на FEnemyData
	//	if (_EnemyData.DataTable->GetRowStruct() == FEnemyData::StaticStruct()) 
	//	{

	//	}
	//}
}

void ASkeletalMeshEnemy::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (_EnemyData.DataTable) 
	{
		if (_EnemyData.DataTable->GetRowStruct() == FEnemyData::StaticStruct())
		{
			auto Data = _EnemyData.DataTable->FindRow<FEnemyData>(_EnemyData.RowName, "");
			_MaxHealth = Data->Health;
			_CurrentHealth = _MaxHealth;
			_RegenHealth = Data->HealthRegeneration;
			_Defense = Data->Defense;
			_MaxDurability = Data->Durability;
			_CurrentDurability = _MaxDurability;
			_RegenDurability = Data->RegenDurability;
			_StartRegenDurability = Data->StartRegenDurability;

			_MonsterLevel = Data->Level;
			_GainedExp = Data->ExpGained;
			_Name = Data->Name;
			_Class = Data->Class;

			_MonsterDamage = Data->Damage;
			_StatList = Data->StatList;
			_ResistanceList = Data->ResistanceList;
		}
	}
}

// Called every frame
void ASkeletalMeshEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkeletalMeshEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASkeletalMeshEnemy::BeginCursorOver(UPrimitiveComponent* TouchedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlapped the mob!"));
}

void ASkeletalMeshEnemy::EndCursorOver(UPrimitiveComponent* TouchedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("End overlap the mob!"));
}
