#include "Character/TDRPGPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATDRPGPlayer::ATDRPGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

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

	// 카메라
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(GetRootComponent());
	springArm->TargetArmLength = 500.f;
	springArm->SocketOffset = FVector(0, 0, 500.f);
	springArm->bUsePawnControlRotation = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm, springArm->SocketName);
	camera->SetRelativeRotation(FRotator(-50, 0, 0));
	camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ATDRPGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

}

