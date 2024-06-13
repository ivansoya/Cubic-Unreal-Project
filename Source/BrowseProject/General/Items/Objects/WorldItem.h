// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemObjects.h"
#include "WorldItem.generated.h"

class UBasicItem;
class UStaticMeshComponent;
class UWidgetComponent;
class UItemTag;

UCLASS()
class BROWSEPROJECT_API AWorldItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldItem();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "World Item")
	UBasicItem* ItemObject = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"), Category = "World Item")
	TSubclassOf<UItemTag> ItemTag;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (DisplayName = "Widget Component"))
	UWidgetComponent* _WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (DisplayName = "Mesh Component"))
	UStaticMeshComponent* _Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (DisplayName = "Default Root Component"))
	USceneComponent* _DefaultRoot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDisplayItems();

	UFUNCTION()
	void OnHideItems();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
