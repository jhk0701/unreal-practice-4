// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame/Dungeon/DungeonGameState.h"
#include "InGame/Dungeon/StartPhase.h"
#include "InGame/Dungeon/WavePhase.h"
#include "InGame/Dungeon/EndPhase.h"
#include "Character/TDRPGEnemy.h"

#include "Core/GameDataManager.h"
#include "Data/StageDataRow.h"

#include "TopDownRPG/TopDownRPG.h"

ADungeonGameState::ADungeonGameState()
{
	// TODO : 데이터 기반 생성으로 변경
	ConstructorHelpers::FClassFinder<ATDRPGEnemy> tempEnemy(TEXT("Blueprint'/Game/2-Blueprints/Enemy/BP_TDRPGEnemy.BP_TDRPGEnemy_C'"));
	if (tempEnemy.Succeeded())
		enemyFactory = tempEnemy.Class;
}

void ADungeonGameState::BeginPlay()
{
	Super::BeginPlay();

	// 페이즈 세팅
	PhaseMap.Add(EPhaseType::Start, NewObject<UStartPhase>());
	PhaseMap.Add(EPhaseType::Wave, NewObject<UWavePhase>());
	PhaseMap.Add(EPhaseType::End, NewObject<UEndPhase>());

	for (auto iter = PhaseMap.CreateConstIterator(); iter; ++iter)
		iter->Value->InitPhase(this);
	
	Transition(EPhaseType::Start);
}

void ADungeonGameState::Transition(EPhaseType Phase)
{
	if (CurPhase)
		CurPhase->Exit();

	CurPhase = PhaseMap[Phase];
	
	CurPhase->Enter();
}

void ADungeonGameState::SpawnEnemy(const FString& EnemyID)
{
	if (!enemyFactory)
	{
		PRINT_LOG(TEXT("Enemy to spawn is null."));
		return;
	}

	FVector SpawnLoc = spawnPoint;
	SpawnLoc.X += FMath::RandRange(-spawningRadius, spawningRadius);
	SpawnLoc.Y += FMath::RandRange(-spawningRadius, spawningRadius);
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLoc);
	SpawnTransform.SetRotation(FQuat::Identity);

	GetWorld()->SpawnActor<AActor>(enemyFactory, SpawnTransform);

	++EnemyCount;
}

void ADungeonGameState::OnEnemyDead()
{
	if (EnemyCount == 0)
		return;

	--EnemyCount;

	if (EnemyCount == 0)
	{
		PRINT_LOG(TEXT("Wave Ended"));
		ProceedWave();
	}
}

void ADungeonGameState::ProceedWave()
{
	// 현재 스테이지 데이터 로드
	UGameDataManager* GameData = GetGameInstance()->GetSubsystem<UGameDataManager>();
	FStageDataRow* StageData = GameData->GetRow<FStageDataRow>(ETableType::Stage, *CurStageId);
	
	// CurWaveIdx 가 마지막 Idx면 종료
	// Wave 재개 CurWaveIdx는 Wave Exit에서 +1
	Transition(StageData->EnemyListPerWave.Num() - 1 == CurWaveIdx ? EPhaseType::End : EPhaseType::Wave);
}
