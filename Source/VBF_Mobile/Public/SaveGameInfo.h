// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameInfo.generated.h"

/**
 * 
 */
UCLASS()
class VBF_MOBILE_API USaveGameInfo : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnyWhere, Category = Basic)
		FString SlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	USaveGameInfo();
	
};
