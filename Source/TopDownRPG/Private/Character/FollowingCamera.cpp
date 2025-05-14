// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FollowingCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFollowingCamera::AFollowingCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	// 카메라
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(root);
	springArm->TargetArmLength = 500.f;
	springArm->SocketOffset = FVector(0, 0, 500.f);
	springArm->bUsePawnControlRotation = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm, springArm->SocketName);
	camera->SetRelativeRotation(FRotator(-50, 0, 0));
	camera->bUsePawnControlRotation = false;
}

// Called every frame
void AFollowingCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (followingTarget)
		SetActorLocation(followingTarget->GetActorLocation());
}

