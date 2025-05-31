// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/InteractBase.h"
#include "CommonConst.h"
#include <Components/BoxComponent.h>

#include "TopDownRPG/TopDownRPG.h"

// Sets default values
AInteractBase::AInteractBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Collider"));
	InteractCollider->InitBoxExtent(FVector(300));
	InteractCollider->SetGenerateOverlapEvents(true);
	InteractCollider->SetCollisionProfileName(CommonConst::Interaction_ProfileName);
}

void AInteractBase::BeginPlay()
{
	Super::BeginPlay();

	InteractCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AInteractBase::OnBeginOverlapped);
	InteractCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &AInteractBase::OnEndOverlapped);
}


void AInteractBase::OnBeginOverlapped(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	PRINT_LOG(TEXT("On Overlap Begin"));
}

void AInteractBase::OnEndOverlapped(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	PRINT_LOG(TEXT("On Overlap End"));
}
