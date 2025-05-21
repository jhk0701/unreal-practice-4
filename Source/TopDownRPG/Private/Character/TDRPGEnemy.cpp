#include "Character/TDRPGEnemy.h"
#include "Character/CharacterStatus.h"
#include "Character/CharacterAbility.h"
#include "Character/EnemyFSM.h"
#include "Character/EnemyAttack.h"
#include "Character/EnemyMove.h"
#include "Character/EnemyAnim.h"
#include "Core/DungeonGameState.h"
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h" // 디버깅용

// Sets default values
ATDRPGEnemy::ATDRPGEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	// 서브 컴포넌트 설정
	statusComp = CreateDefaultSubobject<UCharacterStatus>(TEXT("StatusComp"));
	abilityComp = CreateDefaultSubobject<UCharacterAbility>(TEXT("AbilityComp"));
	attackComp = CreateDefaultSubobject<UEnemyAttack>(TEXT("AttackComp"));
	moveComp = CreateDefaultSubobject<UEnemyMove>(TEXT("MoveComp"));

	// 임시 스탯, 어빌리티 세팅
	// TODO : 데이터 테이블에서 받아오기
	statusComp->InitStatus({ EStatus::Hp, EStatus::Mp }, { 100, 100 });
	abilityComp->InitAbility({ 10,10,10 });

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

	Tags.Add(GetTag());

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

	statusComp->OnCharacterDead.AddUObject(this, &ATDRPGEnemy::Die);
	animInst = Cast<UEnemyAnim>(skinMesh->GetAnimInstance());
}

void ATDRPGEnemy::TakeDamage(int32 Damage)
{
	// TODO : 언리얼 데미지 시스템으로 변경
	statusComp->SubtractStat(EStatus::Hp, Damage);
	animInst->PlayHit();
}

void ATDRPGEnemy::Die()
{
	PRINT_LOG(TEXT("%s is died"), *GetActorNameOrLabel());
	stateMachine->Transition(EEnemyState::Dead);

	ADungeonGameState* state = Cast<ADungeonGameState>(GetWorld()->GetGameState());
	state->OnEnemyDead();
}
