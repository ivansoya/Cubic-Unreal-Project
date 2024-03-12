// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Element.generated.h"

/**
 * ����� ��������� �������������� �����
 */
UCLASS(Blueprintable)
class BROWSEPROJECT_API UElementalDamageType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Meta = (DisplayName = "�������� ��������"))
	FString Name;

	UPROPERTY(BlueprintReadWrite, Meta = (DisplayName = "���� ������"))
	FColor TextColor;

	// ����� ��� �������, ������� ������������� ��� ��������� �����
};


UCLASS()
class BROWSEPROJECT_API UElementalSystem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Elemental Damage")
	static void SetEffectOnTarget();
};


