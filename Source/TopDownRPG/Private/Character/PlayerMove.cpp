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

	Controller = Cast<ATDRPGPlayerController>(Player->GetController());
	MoveComp = Player->GetCharacterMovement();

	Player->OnAttackCalled.AddUObject(this, &UPlayerMove::StopMove);
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
	if (Player->GetMouseToWorld(hitResult))
	{
		Destination = hitResult.ImpactPoint;
		Destination.Z = 0.0f;
		bIsWalking = true;
	}
}

void UPlayerMove::StopMove()
{
	bIsWalking = false;
	Destination = Player->GetActorLocation();
	MoveComp->StopMovementImmediately();
}

void UPlayerMove::Move(float DeltaTime)
{
	if (!bIsWalking) 
		return;

	FVector PlayerLoc = Player->GetActorLocation();
	PlayerLoc.Z = 0.0f;
		
	FVector Dir = (Destination - PlayerLoc);

	if (Dir.SquaredLength() < ToleranceToDestination * ToleranceToDestination)
	{
		bIsWalking = false;
		return;
	}

	FVector Input = DeltaTime * Speed * Dir.GetSafeNormal();
	MoveComp->AddInputVector(Input);
}

void UPlayerMove::InputDodge(const FInputActionValue& InputValue)
{
	Dodge();
}

void UPlayerMove::Dodge()
{
	StopMove();
	MoveComp->Launch(Player->GetActorForwardVector() * DodgePower);
}

