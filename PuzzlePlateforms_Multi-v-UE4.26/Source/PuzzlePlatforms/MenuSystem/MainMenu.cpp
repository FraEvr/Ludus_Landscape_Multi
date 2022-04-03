// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"




bool UMainMenu::Initialize(){
 
     /*cmdHost = (UButton*) GetWidgetFromName(TEXT("cmdHost"));
     cmdHost->OnClicked.AddDynamic(this, &UMainMenu::hostServer);*/

    bool Success = Super::Initialize();
    if (!Success) return false;
    
    if (!ensure(cmdHost != nullptr)) return false;

	cmdHost->OnClicked.AddDynamic(this, &UMainMenu::hostServer);


	if (!ensure(cmdJoin != nullptr)) return false;
		
	cmdJoin->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(cmdCancelJoinMenuButton != nullptr)) return false;

	cmdCancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(cmdConfirmJoinMenuButton != nullptr)) return false;

	cmdConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::joinServer);

	if (!ensure(cmdQuitGame != nullptr)) return false;

	cmdQuitGame->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);


    return true;

	
}




void UMainMenu::hostServer(){

	

    if (MenuInterface != nullptr)
    {
        MenuInterface->Host();
    }

}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}


void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}



void UMainMenu::joinServer(){

	//UE_LOG(LogTemp, Warning, TEXT("I m gonna join a server!!"));

	if (MenuInterface != nullptr)
	{
		if (!ensure(txtIpadressField != nullptr)) return;
		const FString &Address = txtIpadressField->GetText().ToString();
		MenuInterface->Join(Address);
	}

}


void UMainMenu::QuitPressed(){

	//UE_LOG(LogTemp, Warning, TEXT("I quit game!!"));

    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    PlayerController->ConsoleCommand("quit");


}

