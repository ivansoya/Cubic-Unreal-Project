// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FIcon.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FIcon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Icon 76px") )
	UTexture2D* IconTexture_76px;
};
