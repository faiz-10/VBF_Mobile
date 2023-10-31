
// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPlayerController.h"

void ALoginPlayerController::SaveInfo(FString PlayerName)
{
	if (USaveGameInfo* SaveGameInfo = Cast<USaveGameInfo>(UGameplayStatics::CreateSaveGameObject(USaveGameInfo::StaticClass()))) {
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		SavedDelegate.BindUObject(this, &ALoginPlayerController::SaveGameDelegateFunction);
		SaveGameInfo->PlayerName = PlayerName;
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInfo, "Slot_Name", 0, SavedDelegate);
	}
}

void ALoginPlayerController::SaveGameDelegateFunction(const FString& SlotName, const int32 UserIndex, bool Success)
{

}
