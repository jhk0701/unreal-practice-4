#include "Character/TDRPGPlayer.h"
#include "Character/PlayerMove.h"

// Sets default values for this component's properties
UPlayerMove::UPlayerMove()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


void UPlayerMove::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<ATDRPGPlayer>(GetOwner());
	camera = me->GetCamera();
}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

}

void UPlayerMove::SetupInputBinding(UInputComponent* PlayerInputComponent, APlayerController* InController)
{

}
