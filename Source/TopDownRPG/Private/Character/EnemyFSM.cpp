#include "Character/EnemyFSM.h"
#include "Character/TDRPGEnemy.h"
#include "Character/FSM/IdleState.h"
#include "Character/FSM/MoveState.h"
#include "Character/FSM/AttackState.h"
#include "Character/FSM/DeadState.h"

UEnemyFSM::UEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UEnemyFSM::InitializeComponent()
{
	Super::InitializeComponent();

	Owner = Cast<ATDRPGEnemy>(GetOwner());
	
	StateMap.Add(EEnemyState::Idle, NewObject<UIdleState>());
	StateMap.Add(EEnemyState::Move, NewObject<UMoveState>());
	StateMap.Add(EEnemyState::Attack, NewObject<UAttackState>());
	StateMap.Add(EEnemyState::Dead, NewObject<UDeadState>());

	for (auto Iter = StateMap.CreateConstIterator(); Iter; ++Iter)
		Iter->Value->Initialize(this);
}

void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	Transition(EEnemyState::Idle);
}

void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurState)
		CurState->Update(DeltaTime);
}

void UEnemyFSM::Transition(EEnemyState Type)
{
	if (CurState)
		CurState->Exit();

	CurState = StateMap[Type];

	CurState->Enter();
}

TObjectPtr<ATDRPGEnemy> UEnemyFSM::GetOwnerEnemy()
{
	if(!Owner)
		Owner = Cast<ATDRPGEnemy>(GetOwner());

	return Owner;
}

