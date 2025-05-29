#include "Character/PlayerMove.h"
#include "Character/TDRPGPlayer.h"
#include "Core/TDRPGPlayerController.h"
#include <EnhancedInputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>

#include "TopDownRPG/TopDownRPG.h"

UPlayerMove::UPlayerMove()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	controller = Cast<ATDRPGPlayerController>(player->GetController());
	moveComp = player->GetCharacterMovement();

	player->OnAttackCalled.AddUObject(this, &UPlayerMove::StopMove);
}

void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move(DeltaTime);
}

void UPlayerMove::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);
	
	PlayerInputComponent->BindAction(InController->ClickAction, ETriggerEvent::Started, this, &UPlayerMove::InputClick);
	PlayerInputComponent->BindAction(InController->DodgeAction, ETriggerEvent::Triggered, this, &UPlayerMove::InputDodge);
}

void UPlayerMove::InputClick(const FInputActionValue& InputValue)
{
	FHitResult hitResult;
	if (player->GetMouseToWorld(hitResult))
	{
		Destination = hitResult.ImpactPoint;
		Destination.Z = 0.0f;
		bIsWalking = true;
	}
}

void UPlayerMove::StopMove()
{
	bIsWalking = false;
	Destination = player->GetActorLocation();
	moveComp->StopMovementImmediately();
}

void UPlayerMove::Move(float DeltaTime)
{
	if (!bIsWalking) 
		return;

	FVector playerLoc = player->GetActorLocation();
	playerLoc.Z = 0.0f;
		
	FVector dir = (Destination - playerLoc);

	if (dir.SquaredLength() < ToleranceToDestination * ToleranceToDestination)
	{
		bIsWalking = false;
		return;
	}

	FVector input = DeltaTime * Speed * dir.GetSafeNormal();
	moveComp->AddInputVector(input);
}

void UPlayerMove::InputDodge(const FInputActionValue& InputValue)
{
	Dodge();
}

void UPlayerMove::Dodge()
{
	StopMove();
	moveComp->Launch(player->GetActorForwardVector() * DodgePower);
}

