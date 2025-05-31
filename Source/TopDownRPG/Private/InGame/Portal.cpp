// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Portal.h"
#include <Components/BoxComponent.h>
#include <Components/CapsuleComponent.h>
#include "InGame/Lobby/LobbyGameMode.h"

APortal::APortal()
{
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	Collider->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	Collider->SetGenerateOverlapEvents(false);
	SetRootComponent(Collider);

	InteractCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
}

void APortal::Interact()
{
	// PRINT_LOG(TEXT("Portal Test"));
	ALobbyGameMode* LobbyMode = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
	LobbyMode->GoToDungeon();
}

