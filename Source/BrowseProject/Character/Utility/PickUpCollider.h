// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpCollider.generated.h"

class UCapsuleComponent;
class AWorldItem;

UCLASS()
class BROWSEPROJECT_API APickUpCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpCollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Capsule Collider", AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UCapsuleComponent> _CapsuleComponent;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "Item To Pick Up", ExposeToSpawn = "true"), Category = "Item")
	AWorldItem* _ItemToPickUp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapPickUpCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPickUpColliderDestroyed(AActor* DestroyedActor);

	UFUNCTION(BlueprintCallable)
	void SetItem(AWorldItem* WorldItem);

	UFUNCTION(BlueprintCallable)
	AWorldItem* GetItem();
};
