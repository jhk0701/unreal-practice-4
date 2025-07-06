#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/EnemyFSM.h"
#include "Character/EnemyAction.h"
#include "Character/EnemyMove.h"
#include "Character/EnemyAnim.h"

#include <Components/CapsuleComponent.h>

#include "TDRPGConst.h"
#include "TDRPGEnum.h"
#include "InGame/Dungeon/DungeonGameState.h"
#include "Core/GameDataManager.h"
#include "Data/CharacterDataRow.h"

#include "TopDownRPG/TopDownRPG.h" // 디버깅용

// Sets default values
ATDRPGEnemy::ATDRPGEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	// 서브 컴포넌트 설정
	DataComp = CreateDefaultSubobject<UCharacterData>(TEXT("DataComp"));
	ActionComp = CreateDefaultSubobject<UEnemyAction>(TEXT("ActionComp"));
	MoveComp = CreateDefaultSubobject<UEnemyMove>(TEXT("MoveComp"));

	// 적 컴포넌트 구성
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitCapsuleSize(20, 90);
	
	SkinMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkinMesh->SetupAttachment(Collider);
	
	// TODO : 데이터 기반 메쉬 불러오기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	if(TempMesh.Succeeded())
	{
		SkinMesh->SetSkeletalMesh(TempMesh.Object);
		SkinMesh->SetRelativeLocationAndRotation(FVector(0,0,-90.f), FRotator(0, -90.0f, 0));
	}

	StateMachine = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSMComp"));
}

// Called when the game starts or when spawned
void ATDRPGEnemy::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FTDRPGConst::TAG_ENEMY);

	if (UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>())
	{
		FCharacterDataRow* Data = GameData->GetRow<FCharacterDataRow>(ETableType::Character, DataComp->ClassID);
		DataComp->Initialize(1, *Data, nullptr);
	}

	DataComp->OnCharacterDead.AddUObject(this, &ATDRPGEnemy::Die);

	AnimInst = Cast<UEnemyAnim>(SkinMesh->GetAnimInstance());
}

void ATDRPGEnemy::TakeDamage(int32 Damage)
{
	PRINT_LOG(TEXT("Enemy Take Damage : %d"), Damage);

	// TODO : 언리얼 데미지 시스템으로 변경
	DataComp->SubtractStat(EStatus::Hp, (uint32)Damage);
	AnimInst->PlayHit();
}

void ATDRPGEnemy::Die()
{
	PRINT_LOG(TEXT("%s is died"), *GetActorNameOrLabel());
	StateMachine->Transition(EEnemyState::Dead);

	ADungeonGameState* State = Cast<ADungeonGameState>(GetWorld()->GetGameState());
	State->OnEnemyDead();
}
