// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ElementalDamageType.generated.h"

/**
 * Класс типизации элементального урона
 */
UCLASS()
class BROWSEPROJECT_API UElementalDamageType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Name"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Text Color"))
	FColor TextColor;

	// Место для эффекта, который накладывается при нанесении урона
};