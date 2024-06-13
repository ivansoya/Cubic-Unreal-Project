// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "System.generated.h"

UCLASS()
class BROWSEPROJECT_API UElementalSystem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Elemental Damage")
	static void SetEffectOnTarget();
};


