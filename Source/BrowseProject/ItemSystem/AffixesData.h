// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AffixesData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BROWSEPROJECT_API FAffixData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int MYUPROPERTY;
};

