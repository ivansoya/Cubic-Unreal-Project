// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ItemTag.generated.h"

class UUserWidget;
class USizeBox;
class UTextBlock;
class UButton;
class AWorldItem;
class URarity;

class UButtonSlot;
class APickUpCollider;

/**
 * Виджет, который нужно использовать для наследования, чтобы создать тип тага над предметом, когда он лежит на полу.
 */
UCLASS(Abstract)
class BROWSEPROJECT_API UItemTag : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetPropertiesWithRarity(URarity* Rarity, FText ItemName);

	UFUNCTION(BlueprintCallable)
	AWorldItem* GetItemRef();

	UFUNCTION(BlueprintCallable)
	void SetItemRef(AWorldItem* Item);

protected:

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadWrite)
	USizeBox* SizeBox;

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadWrite)
	UButton* Button;

	UPROPERTY(meta = (BindWidget), VisibleAnywhere, BlueprintReadWrite)
	UTextBlock* TextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item Reference"), Category = "Item")
	AWorldItem* _ItemRef;

protected:

	UFUNCTION()
	void OnButtonClicked();
	
};
