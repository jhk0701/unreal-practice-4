#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/EnemyFSM.h"
#include "Character/EnemyAttack.h"
#include "Character/EnemyMove.h"
#include "Character/EnemyAnim.h"
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>

#include "CommonConst.h"
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
	AttackComp = CreateDefaultSubobject<UEnemyAttack>(TEXT("AttackComp"));
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

	Tags.Add(CommonConst::EnemyTag);

	// 임시 히트박스
	HitCollider = CreateDefaultSubobject<USphereComponent>(TEXT("TempHit"));
	HitCollider->SetupAttachment(RootComponent);
	HitCollider->SetRelativeLocation(FVector(70.f, 0, 0));
	HitCollider->SetSphereRadius(50.f);
}

// Called when the game starts or when spawned
void ATDRPGEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>())
	{
		FCharacterDataRow* Data = GameData->GetRow<FCharacterDataRow>(ETableType::Character, FName(DataComp->CharID));
		DataComp->Initialize(1, Data);
	}

	DataComp->OnCharacterDead.AddUObject(this, &ATDRPGEnemy::Die);

	AnimInst = Cast<UEnemyAnim>(SkinMesh->GetAnimInstance());
}

void ATDRPGEnemy::TakeDamage(int32 Damage)
{
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
