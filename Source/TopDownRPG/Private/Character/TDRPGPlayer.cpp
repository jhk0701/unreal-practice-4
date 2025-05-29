#include "Character/TDRPGPlayer.h"
#include "Character/CharacterData.h"
#include "Character/PlayerMove.h"
#include "Character/PlayerAttack.h"
#include "Character/PlayerInteraction.h"
#include "Character/PlayerAnim.h"

#include "CommonConst.h"
#include "Core/TDRPGPlayerController.h"
#include "Core/TDGameState.h"
#include "Core/GameDatabaseSystem.h"
#include "Core/UISubsystem.h"

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

	UGameInstance* GameInst = GetGameInstance();

	// 데이터 반영
	if (UGameDatabaseSystem* Database = GameInst->GetSubsystem<UGameDatabaseSystem>())
	{
		// TODO : 플레이어 데이터 반영
		FCharacterDataRow* Data = Database->GetRow<FCharacterDataRow>(ETableType::Character, FName(dataComp->CharID));
		dataComp->Initialize(5, 0, Data);
		
		FPrimaryAssetId ConfigID(CommonConst::AssetType_CharacterConfig, *dataComp->CharID);
		UPrimaryDataAsset* LoadedDataAsset = Database->LoadPrimaryAssetData(ConfigID);

		if (!LoadedDataAsset)
			PRINT_LOG(TEXT("Config is null"));

		UCharacterConfig* Config = Cast<UCharacterConfig>(LoadedDataAsset);
		
		USkeletalMeshComponent* MeshComp = GetMesh();

		if (Config->SkeletalMesh.IsPending())
			Config->SkeletalMesh.LoadSynchronous();

		MeshComp->SetSkeletalMesh(Config->SkeletalMesh.Get());
		MeshComp->SetRelativeLocationAndRotation(FVector(0, 0, -90.f), FRotator(0, -90.f, 0));

		if (Config->Animation.IsPending())
			Config->Animation.LoadSynchronous();

		MeshComp->SetAnimClass(Config->Animation.Get());
	}

	// UI 호출
	if (UUISubsystem* UISystem = GameInst->GetSubsystem<UUISubsystem>()) 
	{
		UISystem->GetUI<UTDRPGUWStatusBar>(
			FOnLoadCompleted::CreateLambda( 
				[this](UTDRPGUserWidget* Loaded){
					UIStatusBar = Cast<UTDRPGUWStatusBar>(Loaded);
					UIStatusBar->InitStatusBar(this);
					UIStatusBar->AddToViewport();
				})
		);
	}
	

	dataComp->OnCharacterDead.AddUObject(this, &ATDRPGPlayer::Die);
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
	dataComp->SubtractStat(EStatus::Hp, (uint32)Damage);
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