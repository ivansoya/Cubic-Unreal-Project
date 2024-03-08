// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rarity.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BROWSEPROJECT_API URarity : public UDataAsset
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Name"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Font Color"))
	FColor FontColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Background Color"))
	FColor BackColor;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Special Effect"))
	//FColor BackColor;
};
