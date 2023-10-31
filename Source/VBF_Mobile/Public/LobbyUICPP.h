// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUICPP.generated.h"

/**
 * 
 */
UCLASS()
class VBF_MOBILE_API ULobbyUICPP : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
		FString Name;
	
};
