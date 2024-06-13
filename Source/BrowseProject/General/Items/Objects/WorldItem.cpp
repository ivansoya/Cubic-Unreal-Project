// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldItem.h"
#include "Components/WidgetComponent.h"
#include "BrowseProject/Character/Interfaces/FunctionalityComponents.h"
#include "BrowseProject/Character/Interfaces/Inventory.h"
#include "BrowseProject/UI/Item/ItemTag.h"

// Sets default values
AWorldItem::AWorldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	_DefaultRoot->SetMobility(EComponentMobility::Movable);
	SetRootComponent(_DefaultRoot);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	_Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	try {
		static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Data/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
		if (MeshAsset.Object != nullptr) {
			UStaticMesh* Asset = MeshAsset.Object;
			_Mesh->SetStaticMesh(Asset);
		}
	}
	catch (...) {

	}

	_Mesh->SetCollisionProfileName("BlockOnlyStatic");
	_Mesh->SetSimulatePhysics(false);

	// Инициализация Виджет компонента
	_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	_WidgetComponent->AttachToComponent(_Mesh, FAttachmentTransformRules::KeepRelativeTransform);

	_WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	_WidgetComponent->SetDrawAtDesiredSize(true);
	_WidgetComponent->SetComponentTickEnabled(false);
	//_WidgetComponent->SetRelativeTransform(FTransform(FRotator(), FVector(0, 0, 100)));

}

void AWorldItem::OnDisplayItems()
{
	auto widget = _WidgetComponent->GetWidget();
	if (widget) {
		widget->SetVisibility(ESlateVisibility::Visible);
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Magenta, TEXT("Display Called"));
	}
}

void AWorldItem::OnHideItems()
{
	auto widget = _WidgetComponent->GetWidget();
	if (widget) {
		widget->SetVisibility(ESlateVisibility::Collapsed);
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, TEXT("Hide Called"));
	}
}

// Called when the game starts or when spawned
void AWorldItem::BeginPlay()
{
	Super::BeginPlay();

	auto CharacterInventory = IFunctionalityComponents::Execute_GetInventoryComponent(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (CharacterInventory) {

		ItemTag = CharacterInventory->GetClassOfItemTag();

		CharacterInventory->GetDisplaySignature().AddDynamic(this, &AWorldItem::OnDisplayItems);
		CharacterInventory->GetHideSignature().AddDynamic(this, &AWorldItem::OnHideItems);
	}
	
	_WidgetComponent->SetWidgetClass(ItemTag);
	_WidgetComponent->InitWidget();

	UItemTag* ItemTag_Prop = Cast<UItemTag>(_WidgetComponent->GetWidget());
	if (ItemTag_Prop && ItemObject) {
		ItemTag_Prop->SetPropertiesWithRarity(ItemObject->Rarity, FText::FromString(ItemObject->Name));
		ItemTag_Prop->SetItemRef(this);
		_Mesh->SetStaticMesh(ItemObject->WorldMesh);
	}
	ItemTag_Prop = nullptr;
}

// Called every frame
void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

