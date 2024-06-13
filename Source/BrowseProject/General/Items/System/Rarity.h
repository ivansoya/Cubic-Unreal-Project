// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rarity.generated.h"

/**
 * 
 */
UCLASS()
class BROWSEPROJECT_API URarity : public UDataAsset
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Name"), Category = "General")
	FString Name;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Info Font Color"), Category = "Item Info Parameters")
	FColor ItemNameInfoColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Info Border Color"), Category = "Item Info Parameters")
	FColor ItemBorderInfoColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Info Background"), Category = "Item Info Parameters")
	UTexture2D* BackgroundTexture;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Tag Text Color"), Category = "Tag Normal Appearance")
	FColor TagTextColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Tag Background Color"), Category = "Tag Normal Appearance")
	FColor TagBackgroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Tag Border Color"), Category = "Tag Normal Appearance")
	FColor TagBorderColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Tag Background Color"), Category = "Tag Hovered Appearance")
	FColor TagBackgroundColor_Hovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Tag Border Color"), Category = "Tag Hovered Appearance")
	FColor TagBorderColor_Hovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Font Size", ClampMin = "10", ClampMax = "36"), Category = "Tag Parameters")
	int FontSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Tag Margin"), Category = "Tag Parameters")
	FVector2D Margin; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Tag Border Width", ClampMin = "0", ClampMax = "12"), Category = "Tag Parameters")
	float TagBorderWidth;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Special Effect"))
	//FColor BackColor;S
};
