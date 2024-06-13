// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTag.h"
#include "BrowseProject/General/Items/System/Rarity.h"
#include "Styling/SlateBrush.h"
#include "Components/ButtonSlot.h"
#include "BrowseProject/General/Items/Objects/WorldItem.h"
#include "BrowseProject/Character/Utility/PickUpCollider.h"
#include "BrowseProject/Character/Interfaces/PickUp.h"

void UItemTag::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemTag::SetPropertiesWithRarity(URarity* Rarity, FText ItemName)
{
	FSlateBrush StyleButton_Normal = FSlateBrush();
	StyleButton_Normal.TintColor = Rarity->TagBackgroundColor;
	StyleButton_Normal.DrawAs = ESlateBrushDrawType::RoundedBox;
	StyleButton_Normal.OutlineSettings = FSlateBrushOutlineSettings(FVector4(0), FSlateColor(Rarity->TagBorderColor), Rarity->TagBorderWidth);

	FSlateBrush StyleButton_Hovered = FSlateBrush();
	StyleButton_Hovered.TintColor = Rarity->TagBackgroundColor_Hovered;
	StyleButton_Hovered.DrawAs = ESlateBrushDrawType::RoundedBox;
	StyleButton_Hovered.OutlineSettings = FSlateBrushOutlineSettings(FVector4(0), FSlateColor(Rarity->TagBorderColor_Hovered), Rarity->TagBorderWidth);

	FButtonStyle ButtonStyleGeneral = FButtonStyle();

	ButtonStyleGeneral.SetNormal(StyleButton_Normal);
	ButtonStyleGeneral.SetHovered(StyleButton_Hovered);
	ButtonStyleGeneral.SetPressed(StyleButton_Normal);

	Button->SetStyle(ButtonStyleGeneral);
	Button->OnClicked.AddDynamic(this, &UItemTag::OnButtonClicked);

	TextBlock->SetText(ItemName);
	TextBlock->SetColorAndOpacity(Rarity->TagTextColor);

	
	TextBlock->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), Rarity->FontSize));

	FSlateBrush TextBlockBrush = FSlateBrush();
	TextBlockBrush.Margin = FMargin(Rarity->Margin);
	TextBlock->SetStrikeBrush(TextBlockBrush);
}

AWorldItem* UItemTag::GetItemRef()
{
	return _ItemRef;
}

void UItemTag::SetItemRef(AWorldItem* Item)
{
	_ItemRef = Item;
}

void UItemTag::OnButtonClicked()
{
	if (_ItemRef) {
		IPickUp::Execute_PickUpItem(GetWorld()->GetFirstPlayerController(), _ItemRef, _ItemRef->GetActorLocation());
	}
}