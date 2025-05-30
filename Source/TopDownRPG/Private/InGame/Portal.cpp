// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Portal.h"
#include <Components/BoxComponent.h>
#include <Components/CapsuleComponent.h>
#include "InGame/Lobby/LobbyGameMode.h"

APortal::APortal()
{
	collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	collider->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	collider->SetGenerateOverlapEvents(false);
	SetRootComponent(collider);

	interactCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
}

void APortal::Interact()
{
	// PRINT_LOG(TEXT("Portal Test"));
	ALobbyGameMode* lobbyMode = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
	lobbyMode->GoToDungeon();
}

