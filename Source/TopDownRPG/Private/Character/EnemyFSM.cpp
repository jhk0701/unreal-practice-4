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

	owner = Cast<ATDRPGEnemy>(GetOwner());
	
	stateMap.Add(EEnemyState::Idle, NewObject<UIdleState>());
	stateMap.Add(EEnemyState::Move, NewObject<UMoveState>());
	stateMap.Add(EEnemyState::Attack, NewObject<UAttackState>());
	stateMap.Add(EEnemyState::Dead, NewObject<UDeadState>());

	for (auto iter = stateMap.CreateIterator(); iter; ++iter)
		iter->Value->Initialize(this);
}

void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	Transition(EEnemyState::Idle);
}

void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (curState)
		curState->Update(DeltaTime);
}

void UEnemyFSM::Transition(EEnemyState type)
{
	if (curState)
		curState->Exit();

	curState = stateMap[type];

	curState->Enter();
}

TObjectPtr<ATDRPGEnemy> UEnemyFSM::GetOwnerEnemy()
{
	if(!owner)
		owner = Cast<ATDRPGEnemy>(GetOwner());

	return owner;
}

