#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"
#include "Character/CharacterStatus.h"
#include "Character/CharacterAbility.h"
#include "Character/PlayerMove.h"
#include "Character/PlayerAttack.h"
#include <EnhancedInputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

// Sets default values
ATDRPGPlayer::ATDRPGPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// 서브 컴포넌트 설정
	statusComp = CreateDefaultSubobject<UCharacterStatus>(TEXT("StatusComp"));
	abilityComp = CreateDefaultSubobject<UCharacterAbility>(TEXT("AbilityComp"));
	moveComp = CreateDefaultSubobject<UPlayerMove>(TEXT("MoveComp"));
	attackComp = CreateDefaultSubobject<UPlayerAttack>(TEXT("AttackComp"));

	// 임시 스탯, 어빌리티 세팅
	// TODO : 데이터 테이블에서 받아오기
	statusComp->InitStatus({ EStatus::Hp, EStatus::Mp }, { 100, 100 });
	abilityComp->InitAbility({ 10,10,10 });

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
	GetCapsuleComponent()->InitCapsuleSize(20.0f, 90.0f);

	// 캐릭터 회전 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터가 향하는 곳을 바라보도록

	// 카메라
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);
	springArm->SetUsingAbsoluteRotation(true); // 캐릭터가 회전해도 카메라 암은 회전하지 않도록 함
	springArm->TargetArmLength = 350.0f;
	springArm->SocketOffset = FVector(0, 0, 600.f);
	springArm->bUsePawnControlRotation = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm, springArm->SocketName);
	camera->SetRelativeRotation(FRotator(-60, 0, 0));
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

	OnInputBindDelegate.Broadcast(Cast<UEnhancedInputComponent>(PlayerInputComponent), Cast<ATDRPGPlayerController>(GetController()));
}

void ATDRPGPlayer::InvokeAttackDelegate()
{
	OnAttackCalled.Broadcast();
}