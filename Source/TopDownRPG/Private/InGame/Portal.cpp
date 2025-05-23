// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Portal.h"
#include "TopDownRPG/TopDownRPG.h"


APortal::APortal()
{
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
}

void APortal::Interact()
{
	PRINT_LOG(TEXT("Portal Test"));
}

