#include "Character/PlayerMove.h"
#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"
#include <EnhancedInputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

UPlayerMove::UPlayerMove()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UPlayerMove::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<ATDRPGPlayer>(GetOwner());

	// TODO : 공통된 것끼리 추후에 리팩토링
	me->OnInputBindDelegate.AddUObject(this, &UPlayerMove::SetupInputBinding);
}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	controller = Cast<ATDRPGPlayerController>(me->GetController());
	moveComp = me->GetCharacterMovement();
	meshComp = Cast<USceneComponent>(me->GetMesh());
}

void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move(DeltaTime);
}

void UPlayerMove::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	PlayerInputComponent->BindAction(InController->ClickAction, ETriggerEvent::Started, this, &UPlayerMove::InputClick);
}

void UPlayerMove::InputClick(const FInputActionValue& InputValue)
{
	if (!controller)
		return;

	// 뷰포트 마우스 위치 -> 월드좌표로 변환
	FVector worldPoint, worldDirection;
	if (!controller->DeprojectMousePositionToWorld(worldPoint, worldDirection))
		return;

	FCollisionQueryParams params;
	FHitResult hitResult;

	if (GetWorld()->LineTraceSingleByChannel(
		hitResult, 
		worldPoint, 
		worldPoint + worldDirection * 10000, 
		ECC_GameTraceChannel1, 
		params))
	{
		Destination = hitResult.ImpactPoint;
	}
}

void UPlayerMove::Move(float DeltaTime)
{
	FVector dir = (Destination - me->GetActorLocation());
	
	if (dir.SquaredLength() < ToleranceToDestination * ToleranceToDestination)
		return;

	moveComp->AddInputVector(DeltaTime * Speed * dir.GetSafeNormal());

	FRotator rot = dir.ToOrientationRotator();
	// meshComp->SetRelativeRotation(dir.ToOrientationRotator());
}