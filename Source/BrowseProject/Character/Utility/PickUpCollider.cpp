// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpCollider.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "BrowseProject/General/Items/Objects/WorldItem.h"
#include "BrowseProject/Character/Interfaces/Inventory.h"

// Sets default values
APickUpCollider::APickUpCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TObjectPtr<USceneComponent> DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>("RootDefaultSceneComponent");
	RootComponent = DefaultSceneComponent;

	_CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
	_CapsuleComponent->SetVisibility(true);
	_CapsuleComponent->SetHiddenInGame(false);
	_CapsuleComponent->SetCapsuleHalfHeight(122);
	_CapsuleComponent->SetCapsuleRadius(50);

	_CapsuleComponent->SetupAttachment(DefaultSceneComponent);
	
	// Назначение функции на подбор предмета при достижении персонажем коллайдера
	_CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUpCollider::OverlapPickUpCharacter);

	// При уничтожении коллайдера остановить персонажа
	this->OnDestroyed.AddDynamic(this, &APickUpCollider::OnPickUpColliderDestroyed);
}

// Called when the game starts or when spawned
void APickUpCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpCollider::OverlapPickUpCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Inventory = Cast<IInventory>(OtherActor);
	if (Inventory == nullptr) {
		return;
	}

	if (_ItemToPickUp && _ItemToPickUp->ItemObject) {
		// Добавляем предмет в инвентарь Актера
		_ItemToPickUp->ItemObject->AddToInventory(OtherActor);
		_ItemToPickUp->Destroy();
	}
	// Удаление коллайдера
	this->Destroy();
}

void APickUpCollider::OnPickUpColliderDestroyed(AActor* DestroyedActor)
{
	_ItemToPickUp = nullptr;
}

void APickUpCollider::SetItem(AWorldItem* WorldItem)
{
	_ItemToPickUp = WorldItem;
}

AWorldItem* APickUpCollider::GetItem()
{
	return _ItemToPickUp;
}

