// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemTag;
class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisplayItemsSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHideItemsSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROWSEPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void DisplayItems() const;

	UFUNCTION(BlueprintCallable)
	void HideItems() const;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UItemTag> GetClassOfItemTag();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Tags", meta = (DisplayName = "Class of Item Tag"))
	TSubclassOf<UItemTag> _UsedTypeOfItemTag;

	UItemObject* _CachedItem;

	UPROPERTY(BlueprintAssignable)
	FOnDisplayItemsSignature _OnDisplayItemsDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHideItemsSignature _OnHideItemsDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnDisplayItemsSignature& GetDisplaySignature();

	FOnHideItemsSignature& GetHideSignature();

	
};
