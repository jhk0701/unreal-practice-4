#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"
#include "Character/PlayerMove.h"
#include "Character/PlayerAttack.h"
#include "Character/PlayerInteraction.h"
#include "Character/PlayerAnim.h"

#include "CommonConst.h"
#include "Core/TDRPGPlayerController.h"
#include "Core/TDRPGGameState.h"
#include "Core/GameDataManager.h"
#include "Core/PlayerManager.h"
#include "Core/UIManager.h"

#include "InGame/Dungeon/DungeonGameState.h"

#include "UI/TDRPGUWStatusBar.h"
#include "Data/CharacterDataRow.h"
#include "Data/CharacterConfig.h"
#include "UI/TDRPGUWQuickSlot.h"
#include "UI/TDRPGUWInventory.h"

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
	DataComp = CreateDefaultSubobject<UCharacterData>(TEXT("DataComp"));
	MoveComp = CreateDefaultSubobject<UPlayerMove>(TEXT("MoveComp"));
	AttackComp = CreateDefaultSubobject<UPlayerAttack>(TEXT("AttackComp"));
	InteractComp = CreateDefaultSubobject<UPlayerInteraction>(TEXT("InteractComp"));

	// 충돌체 설정
	GetCapsuleComponent()->InitCapsuleSize(20.0f, 90.0f);

	// 캐릭터 회전 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터가 향하는 곳을 바라보도록

	// 카메라
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true); // 캐릭터가 회전해도 카메라 암은 회전하지 않도록 함
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SocketOffset = FVector(0, 0, 600.f);
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, SpringArm->SocketName);
	Camera->SetRelativeRotation(FRotator(-60, 0, 0));
	Camera->bUsePawnControlRotation = false;

	Tags.Add(CommonConst::PlayerTag);

	// 임시 히트박스
	HitCollider = CreateDefaultSubobject<USphereComponent>(TEXT("TempHit"));
	HitCollider->SetRelativeLocation(FVector(70.f, 0.0f, 0.0f));
	HitCollider->SetSphereRadius(50.f);
	HitCollider->SetupAttachment(RootComponent);

	InteractCollider = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionCollider"));
	InteractCollider->SetSphereRadius(300);
	InteractCollider->SetCollisionProfileName(CommonConst::Interaction_ProfileName);
	InteractCollider->SetupAttachment(RootComponent);
}

void ATDRPGPlayer::BeginPlay()
{
	Super::BeginPlay();

	ATDRPGGameState* State = Cast<ATDRPGGameState>(GetWorld()->GetGameState());
	State->Player = this;

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
	DataComp->CharID = Player->PlayerData->CharID;

	FCharacterDataRow* Data = Database->GetRow<FCharacterDataRow>(ETableType::Character, *DataComp->CharID);
	DataComp->Initialize(Player->Lv, Data);

	// 캐릭터 동적 구성
	FPrimaryAssetId ConfigID(CommonConst::AssetType_CharacterConfig, *DataComp->CharID);
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
	AnimInst = Cast<UPlayerAnim>(MeshComp->GetAnimInstance());

	// UI 호출
	UUIManager* UIManager = GameInst->GetSubsystem<UUIManager>();
	if (UTDRPGUWStatusBar* StatusUI = UIManager->GetUI<UTDRPGUWStatusBar>())
	{
		StatusUI->InitStatusBar(this);
		StatusUI->Open();
	}
	// UIManager->GetUI<UTDRPGUWQuickSlot>();

	DataComp->OnCharacterDead.AddUObject(this, &ATDRPGPlayer::Die);
}

void ATDRPGPlayer::InvokeAttackDelegate()
{
	OnAttackCalled.Broadcast();
}

void ATDRPGPlayer::TakeDamage(int32 Damage)
{
	DataComp->SubtractStat(EStatus::Hp, (uint32)Damage);
	AnimInst->PlayHit();
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
	FVector WorldPoint, WorldDirection;
	
	ATDRPGPlayerController* PlayerController = Cast<ATDRPGPlayerController>(GetController());
	if (!PlayerController->DeprojectMousePositionToWorld(WorldPoint, WorldDirection))
		return false;

	FCollisionQueryParams Params;

	return GetWorld()->LineTraceSingleByChannel(
		OutResult,
		WorldPoint,
		WorldPoint + WorldDirection * 10000,
		ECC_GameTraceChannel1,
		Params);
}