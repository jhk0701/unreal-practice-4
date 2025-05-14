#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"
#include "Character/PlayerMove.h"
#include "Character/FollowingCamera.h"
#include <EnhancedInputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>

// Sets default values
ATDRPGPlayer::ATDRPGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Initialize();
}

// Called when the game starts or when spawned
void ATDRPGPlayer::BeginPlay()
{
	Super::BeginPlay();

	if(cameraFactory)
	{
		cameraInst = GetWorld()->SpawnActor<AFollowingCamera>(cameraFactory);
		cameraInst->SetTarget(this);
	}
}

// Called every frame
void ATDRPGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATDRPGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	OnInputBindDelegate.Broadcast(Cast<UEnhancedInputComponent>(PlayerInputComponent), Cast<ATDRPGPlayerController>(GetController()));
}

void ATDRPGPlayer::Initialize()
{
	// 서브 컴포넌트 설정
	moveComp = CreateDefaultSubobject<UPlayerMove>(TEXT("MoveComp"));

	// Mesh 설정
	// TODO : 각 클래스별 메시 받기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));
	if (tempMesh.Succeeded())
	{
		USkeletalMeshComponent* meshComp = GetMesh();
		meshComp->SetSkeletalMesh(tempMesh.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -90.f));
		meshComp->SetRelativeRotation(FRotator(0, -90.f, 0));
	}

	// 충돌체 설정
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	GetCapsuleComponent()->SetCapsuleRadius(20.f);

	// cameraFactory
	ConstructorHelpers::FClassFinder<AFollowingCamera> tempCam(TEXT("Blueprint'/Game/2-Blueprints/Player/BP_FollowingCamera.BP_FollowingCamera_C'"));
	if(tempCam.Succeeded())
	{
		cameraFactory = tempCam.Class;
	}
}

