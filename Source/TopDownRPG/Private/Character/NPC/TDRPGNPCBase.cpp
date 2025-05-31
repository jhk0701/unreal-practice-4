// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/TDRPGNPCBase.h"
#include <Components/BoxComponent.h>
#include <Components/CapsuleComponent.h>

#include "TopDownRPG/TopDownRPG.h"

// Sets default values
ATDRPGNPCBase::ATDRPGNPCBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// 기본 콜라이더
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->InitCapsuleSize(30, 90);
	Collider->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	Collider->SetGenerateOverlapEvents(false);

	SetRootComponent(Collider);

	// 기본 메시
	SkinnedMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkinnedMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
	if (TempMesh.Succeeded())
	{
		SkinnedMesh->SetSkeletalMesh(TempMesh.Object);
		SkinnedMesh->SetRelativeLocationAndRotation(FVector(0,0,-90), FRotator(0, -90, 0));
	}

	InteractCollider->SetupAttachment(RootComponent);

}
