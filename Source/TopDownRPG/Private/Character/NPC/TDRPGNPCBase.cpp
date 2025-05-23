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
	collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	collider->InitCapsuleSize(30, 90);
	collider->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	collider->SetGenerateOverlapEvents(false);

	SetRootComponent(collider);

	// 기본 메시
	skinnedMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	skinnedMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
	if (tempMesh.Succeeded()) 
	{
		skinnedMesh->SetSkeletalMesh(tempMesh.Object);
		skinnedMesh->SetRelativeLocationAndRotation(FVector(0,0,-90), FRotator(0, -90, 0));
	}

	interactCollider->SetupAttachment(RootComponent);

}
