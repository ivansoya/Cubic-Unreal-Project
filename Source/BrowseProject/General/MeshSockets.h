// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeshSockets.generated.h"

/// <summary>
/// A class that provides the names of the player's skeleton sockets for meshes
/// </summary>
UCLASS()
class BROWSEPROJECT_API UWeaponSocketNames : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(CallInEditor, BlueprintCallable)
	static TArray<FName> GetSocketOptions()
	{
		return {
			"Soc_RightHand",
			"Soc_LeftHand",
			"Soc_ShieldArmed",
			"Soc_ShieldHided",
			"Soc_RightTwoHanded_Hided",
			"Soc_LeftTwoHanded_Hided",
			"Soc_RightHand_Hided",
			"Soc_LeftHand_Hided",
		};
	}
};