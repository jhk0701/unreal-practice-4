#include "Character/TDRPGEnemy.h"
#include "Character/CharacterStatus.h"
#include "Character/CharacterAbility.h"
#include "Character/EnemyFSM.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATDRPGEnemy::ATDRPGEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// 서브 컴포넌트 설정
	statusComp = CreateDefaultSubobject<UCharacterStatus>(TEXT("StatusComp"));
	abilityComp = CreateDefaultSubobject<UCharacterAbility>(TEXT("AbilityComp"));

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
}

// Called when the game starts or when spawned
void ATDRPGEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATDRPGEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

