#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"
#include "Character/PlayerMove.h"
#include "Character/PlayerAttack.h"
#include "Character/PlayerInteraction.h"
#include "Character/PlayerAnim.h"

#include "CommonConst.h"
#include "Core/TDRPGPlayerController.h"
#include "Core/TDGameState.h"
#include "Core/GameDataManager.h"
#include "Core/PlayerManager.h"
#include "Core/UIManager.h"

#include "InGame/Dungeon/DungeonGameState.h"

#include "UI/TDRPGUWStatusBar.h"
#include "Data/CharacterDataRow.h"
#include "Data/CharacterConfig.h"

#include <EnhancedInputComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"


// Sets default values
ATDRPGPlayer::ATDRPGPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// 서브 컴포넌트 설정
	dataComp = CreateDefaultSubobject<UCharacterData>(TEXT("DataComp"));
	moveComp = CreateDefaultSubobject<UPlayerMove>(TEXT("MoveComp"));
	attackComp = CreateDefaultSubobject<UPlayerAttack>(TEXT("AttackComp"));
	interactComp = CreateDefaultSubobject<UPlayerInteraction>(TEXT("InteractComp"));

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

	Initialize();
}

// Called to bind functionality to input
void ATDRPGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	OnInputBindDelegate.Broadcast(Cast<UEnhancedInputComponent>(PlayerInputComponent), Cast<ATDRPGPlayerController>(GetController()));
}

void ATDRPGPlayer::Initialize()
{
	UGameInstance* GameInst = GetGameInstance();

	// 데이터 반영
	UPlayerManager* Player = GameInst->GetSubsystem<UPlayerManager>();
	UGameDataManager* Database = GameInst->GetSubsystem<UGameDataManager>();
	dataComp->CharID = Player->GetPlayerData().CharID;

	FCharacterDataRow* Data = Database->GetRow<FCharacterDataRow>(ETableType::Character, *dataComp->CharID);
	dataComp->Initialize(Player->Lv, Data);

	// 캐릭터 동적 구성
	FPrimaryAssetId ConfigID(CommonConst::AssetType_CharacterConfig, *dataComp->CharID);
	UPrimaryDataAsset* LoadedDataAsset = Database->LoadPrimaryAssetData(ConfigID);

	UCharacterConfig* Config = Cast<UCharacterConfig>(LoadedDataAsset);

	USkeletalMeshComponent* MeshComp = GetMesh();

	/*
	if (Config->SkeletalMesh.IsPending())
		Config->SkeletalMesh.LoadSynchronous();
	*/

	MeshComp->SetSkeletalMesh(Config->SkeletalMesh.Get());
	MeshComp->SetRelativeLocationAndRotation(FVector(0, 0, -90.f), FRotator(0, -90.f, 0));

	/*
	if (Config->Animation.IsPending())
		Config->Animation.LoadSynchronous();
	*/

	MeshComp->SetAnimInstanceClass(Config->Animation.Get());
	animInst = Cast<UPlayerAnim>(MeshComp->GetAnimInstance());

	// UI 호출
	UUIManager* UIManager = GameInst->GetSubsystem<UUIManager>();
	UIManager->GetUI<UTDRPGUWStatusBar>(
		FOnLoadCompleted::CreateLambda(
			[this](UTDRPGUserWidget* Loaded) {
				UIStatusBar = Cast<UTDRPGUWStatusBar>(Loaded);
				UIStatusBar->InitStatusBar(this);
				UIStatusBar->AddToViewport();
			})
	);


	dataComp->OnCharacterDead.AddUObject(this, &ATDRPGPlayer::Die);
}

void ATDRPGPlayer::InvokeAttackDelegate()
{
	OnAttackCalled.Broadcast();
}

void ATDRPGPlayer::TakeDamage(int32 Damage)
{
	dataComp->SubtractStat(EStatus::Hp, (uint32)Damage);
	animInst->PlayHit();
}

void ATDRPGPlayer::Die()
{
	// 던전이라면 스테이지 종료 : 결과 실패
	if (ADungeonGameState* DungeonState = Cast<ADungeonGameState>(GetWorld()->GetGameState()))
		DungeonState->FinishStage(EStageResult::Failed);
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