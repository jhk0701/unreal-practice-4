// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/FSM/IdleState.h"
#include "Character/EnemyFSM.h"
#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include <Kismet/GameplayStatics.h>

#include "InGame/Dungeon/DungeonGameMode.h"
#include "InGame/Dungeon/DungeonGameState.h"

#include "TopDownRPG/TopDownRPG.h"

void UIdleState::Enter()
{
	Super::Enter();

	if (ATDRPGEnemy* Enemy = Machine->GetOwnerEnemy())
	{
		ADungeonGameState* State = Cast<ADungeonGameState>(Machine->GetWorld()->GetGameState());
		Enemy->Target = State->Player;
		
		Machine->Transition(EEnemyState::Move);
	}
	else
	{
		PRINT_LOG(TEXT("machine -> owner is null"));
	}
	
}
