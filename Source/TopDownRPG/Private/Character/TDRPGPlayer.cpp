#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"
#include "Character/PlayerMove.h"
#include "Character/PlayerAction.h"
#include "Character/PlayerInteraction.h"
#include "Character/CharacterAnimBase.h"
#include "Character/PlayerAnim.h"

#include "TDRPGConst.h"
#include "TDRPGEnum.h"
#include "Core/TDRPGPlayerController.h"
#include "Core/TDRPGGameState.h"
#include "Core/GameDataManager.h"
#include "Core/PlayerManager.h"
#include "Core/UIManager.h"

#include "InGame/Dungeon/DungeonGameState.h"

#include "UI/TDRPGUWPlayerUI.h"
#include "UI/TDRPGUWStatusBar.h"
#include "UI/TDRPGUWQuickSlot.h"
#include "UI/TDRPGUWSkillSet.h"

#include "UI/TDRPGUWInventory.h"
#include "UI/TDRPGUWEquipment.h"
#include "UI/TDRPGUWStatusWindow.h"
#include "UI/TDRPGUWSkillWindow.h"

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
	DataComp = CreateDefaultSubobject<UCharacterData>(TEXT("DataComp"));
	MoveComp = CreateDefaultSubobject<UPlayerMove>(TEXT("MoveComp"));
	ActionComp = CreateDefaultSubobject<UPlayerAction>(TEXT("ActionComp"));
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

	InteractCollider = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionCollider"));
	InteractCollider->SetSphereRadius(300);
	InteractCollider->SetCollisionProfileName(FTDRPGConst::INTERACT_PROFILE);
	InteractCollider->SetupAttachment(RootComponent);
}

void ATDRPGPlayer::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FTDRPGConst::TAG_PLAYER);

	ATDRPGGameState* State = Cast<ATDRPGGameState>(GetWorld()->GetGameState());
	State->Player = this;

	Initialize();
}

// Called to bind functionality to input
void ATDRPGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	OnInputBinded.Broadcast(Cast<UEnhancedInputComponent>(PlayerInputComponent), Cast<ATDRPGPlayerController>(GetController()));
}

void ATDRPGPlayer::Initialize()
{
	UGameInstance* GameInst = GetGameInstance();

	// 데이터 반영
	UPlayerManager* Player = GameInst->GetSubsystem<UPlayerManager>();
	DataComp->ClassID = Player->GetCharID();

	UGameDataManager* Database = GameInst->GetSubsystem<UGameDataManager>();
	FCharacterDataRow* Data = Database->GetRow<FCharacterDataRow>(ETableType::Character, DataComp->ClassID);
	DataComp->Initialize(Player->Lv, *Data, Player->Equipment);
	ActionComp->SetSkill(Data->SkillID);

	// 캐릭터 동적 구성
	LoadConfig();
	
	// UI 바인딩
	UUIManager* UIManager = GameInst->GetSubsystem<UUIManager>();
	if (UTDRPGUWPlayerUI* PlayerUI = UIManager->GetUI<UTDRPGUWPlayerUI>()) 
	{
		PlayerUI->StatusBar->Bind(this);
		PlayerUI->QuickSlot->Bind(Player->QuickSlot);
		PlayerUI->SkillSet->Bind(Player->SkillSet, ActionComp);
	}

	if (UTDRPGUWStatusWindow* StatusWind = UIManager->GetUI<UTDRPGUWStatusWindow>())
		StatusWind->Bind(Player);

	if (UTDRPGUWInventory* Inventory = UIManager->GetUI<UTDRPGUWInventory>())
		Inventory->Bind(Player);

	if (UTDRPGUWEquipment* Equipment = UIManager->GetUI<UTDRPGUWEquipment>())
		Equipment->Bind(Player->Equipment);

	if (UTDRPGUWSkillWindow* SkillWind = UIManager->GetUI<UTDRPGUWSkillWindow>())
		SkillWind->Bind(ActionComp);

	DataComp->OnCharacterDead.AddUObject(this, &ATDRPGPlayer::Die);
}

void ATDRPGPlayer::LoadConfig()
{
	UGameInstance* GameInst = GetGameInstance();
	UGameDataManager* Database = GameInst->GetSubsystem<UGameDataManager>();

	FPrimaryAssetId ConfigID(FTDRPGConst::CONFIG_CHARACTER, *DataComp->ClassID);
	UPrimaryDataAsset* LoadedDataAsset = Database->LoadPrimaryAssetData(ConfigID);
	UCharacterConfig* Config = Cast<UCharacterConfig>(LoadedDataAsset);

	USkeletalMeshComponent* MeshComp = GetMesh();
	MeshComp->SetSkeletalMesh(Config->SkeletalMesh);
	MeshComp->SetRelativeLocationAndRotation(FVector(0, 0, -90.f), FRotator(0, -90.f, 0));

	MeshComp->SetAnimInstanceClass(Config->Animation);
	AnimInst = Cast<UPlayerAnim>(MeshComp->GetAnimInstance());
}

inline TObjectPtr<UCharacterAnimBase> ATDRPGPlayer::GetAnim() const
{
	return Cast<UCharacterAnimBase>(AnimInst);
}

void ATDRPGPlayer::InvokeAttackDelegate()
{
	OnAttackInvoked.Broadcast();
}

void ATDRPGPlayer::TakeDamage(int32 Damage)
{
	uint32 Def = DataComp->GetDefensePower();
	Damage = FMath::Max<int32>(Damage - Def, 0);

	PRINT_LOG(TEXT("Player Take Damage : %d"), Damage);

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
	Params.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(
		OutResult,
		WorldPoint,
		WorldPoint + WorldDirection * 10000,
		ECC_GameTraceChannel1,
		Params);
}

bool ATDRPGPlayer::CheckPlayerIsDead() const
{
	return DataComp->bIsDead;
}
