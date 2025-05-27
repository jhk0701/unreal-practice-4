#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/EnemyFSM.h"
#include "Character/EnemyAttack.h"
#include "Character/EnemyMove.h"
#include "Character/EnemyAnim.h"
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>

#include "CommonConst.h"
#include "Core/DungeonGameState.h"
#include "Core/GameDatabaseSystem.h"
#include "Data/CharacterDataRow.h"

#include "TopDownRPG/TopDownRPG.h" // 디버깅용

// Sets default values
ATDRPGEnemy::ATDRPGEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	// 서브 컴포넌트 설정
	dataComp = CreateDefaultSubobject<UCharacterData>(TEXT("DataComp"));
	attackComp = CreateDefaultSubobject<UEnemyAttack>(TEXT("AttackComp"));
	moveComp = CreateDefaultSubobject<UEnemyMove>(TEXT("MoveComp"));

	// 적 컴포넌트 구성
	collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	SetRootComponent(collider);
	collider->InitCapsuleSize(20, 90);
	
	skinMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	skinMesh->SetupAttachment(collider);
	
	// TODO : 데이터 기반 메쉬 불러오기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	if(tempMesh.Succeeded())
	{
		skinMesh->SetSkeletalMesh(tempMesh.Object);
		skinMesh->SetRelativeLocationAndRotation(FVector(0,0,-90.f), FRotator(0, -90.0f, 0));
	}

	stateMachine = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSMComp"));

	Tags.Add(CommonConst::EnemyTag);

	// 임시 히트박스
	hitCollider = CreateDefaultSubobject<USphereComponent>(TEXT("TempHit"));
	hitCollider->SetupAttachment(RootComponent);
	hitCollider->SetRelativeLocation(FVector(70.f, 0, 0));
	hitCollider->SetSphereRadius(50.f);
}

// Called when the game starts or when spawned
void ATDRPGEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (UGameDatabaseSystem* database = GetGameInstance()->GetSubsystem<UGameDatabaseSystem>())
	{
		FCharacterDataRow* data = database->GetRow<FCharacterDataRow>(ETableType::Character, FName(dataComp->CharID));
		dataComp->Initialize(1, 100, data);
	}

	dataComp->OnCharacterDead.AddUObject(this, &ATDRPGEnemy::Die);

	animInst = Cast<UEnemyAnim>(skinMesh->GetAnimInstance());
}

void ATDRPGEnemy::TakeDamage(int32 Damage)
{
	// TODO : 언리얼 데미지 시스템으로 변경
	dataComp->SubtractStat(EStatus::Hp, (uint32)Damage);
	animInst->PlayHit();
}

void ATDRPGEnemy::Die()
{
	PRINT_LOG(TEXT("%s is died"), *GetActorNameOrLabel());
	stateMachine->Transition(EEnemyState::Dead);

	ADungeonGameState* state = Cast<ADungeonGameState>(GetWorld()->GetGameState());
	state->OnEnemyDead();
}
