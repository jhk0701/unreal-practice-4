#include "Character/TDRPGPlayer.h"
#include "Character/CharacterStatus.h"
#include "Character/CharacterAbility.h"
#include "Character/PlayerMove.h"
#include "Character/PlayerAttack.h"
#include "Character/PlayerInteraction.h"
#include "Character/PlayerAnim.h"
#include <EnhancedInputComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>

#include "CommonConst.h"
#include "Core/TDRPGPlayerController.h"
#include "Core/TDGameState.h"
#include "Core/DungeonGameMode.h"
#include "Core/GameDatabaseSystem.h"

#include "TopDownRPG/TopDownRPG.h"
#include "UI/TDRPGUWStatusBar.h"

// Sets default values
ATDRPGPlayer::ATDRPGPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// 서브 컴포넌트 설정
	statusComp = CreateDefaultSubobject<UCharacterStatus>(TEXT("StatusComp"));
	abilityComp = CreateDefaultSubobject<UCharacterAbility>(TEXT("AbilityComp"));
	moveComp = CreateDefaultSubobject<UPlayerMove>(TEXT("MoveComp"));
	attackComp = CreateDefaultSubobject<UPlayerAttack>(TEXT("AttackComp"));
	interactComp = CreateDefaultSubobject<UPlayerInteraction>(TEXT("InteractComp"));

	// 임시 스탯, 어빌리티 세팅
	// TODO : 데이터 테이블에서 받아오기
	statusComp->InitStatus({ EStatus::Hp, EStatus::Mp }, { 100, 100 });
	abilityComp->InitAbility({ 100,10,10 });

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

	Tags.Add(CommonConst::PlayerTag);

	// 임시 히트박스
	hitCollider = CreateDefaultSubobject<USphereComponent>(TEXT("TempHit"));
	hitCollider->SetRelativeLocation(FVector(70.f, 0.0f, 0.0f));
	hitCollider->SetSphereRadius(50.f);
	hitCollider->SetupAttachment(RootComponent);

	interactCollider = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionCollider"));
	interactCollider->SetSphereRadius(300);
	interactCollider->SetCollisionProfileName(CommonConst::Interaction_ProfileName);
	interactCollider->SetupAttachment(RootComponent);
}

void ATDRPGPlayer::BeginPlay()
{
	Super::BeginPlay();

	ATDGameState* state = Cast<ATDGameState>(GetWorld()->GetGameState());
	state->player = this;

	statusComp->OnCharacterDead.AddUObject(this, &ATDRPGPlayer::Die);

	// TODO : 임시 UI 하드코딩 제거
	if (StatusBarFactory)
	{
		StatusBarInst = CreateWidget<UTDRPGUWStatusBar>(GetWorld(), StatusBarFactory, TEXT("Character Status Bar"));
		StatusBarInst->InitStatusBar(this);
		StatusBarInst->AddToViewport();
	}

	animInst = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());

	UGameDatabaseSystem* database = GetGameInstance()->GetSubsystem<UGameDatabaseSystem>();
	if (database)
	{
		auto rowNames = database->GameDatabase[ETableType::Character]->GetRowNames();
		for (int32 i = 0; i < rowNames.Num(); i++)
		{
			PRINT_LOG(TEXT("[%d] : %s"), i, *rowNames[i].ToString());
		}
	}
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

void ATDRPGPlayer::TakeDamage(int32 Damage)
{
	statusComp->SubtractStat(EStatus::Hp, Damage);
	animInst->PlayHit();
}

void ATDRPGPlayer::Die()
{
	PRINT_LOG(TEXT("%s is died"), *GetActorNameOrLabel());
}

bool ATDRPGPlayer::GetMouseToWorld(FHitResult& OutResult)
{
	// 뷰포트 마우스 위치 -> 월드좌표로 변환
	FVector worldPoint, worldDirection;

	ATDRPGPlayerController* controller = Cast<ATDRPGPlayerController>(GetController());
	if (!controller->DeprojectMousePositionToWorld(worldPoint, worldDirection))
		return false;

	FCollisionQueryParams params;

	return GetWorld()->LineTraceSingleByChannel(
		OutResult,
		worldPoint,
		worldPoint + worldDirection * 10000,
		ECC_GameTraceChannel1,
		params);
}