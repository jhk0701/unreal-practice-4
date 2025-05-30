// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/FSM/IdleState.h"
#include "Character/EnemyFSM.h"
#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Kismet/GameplayStatics.h"

#include "InGame/Dungeon/DungeonGameMode.h"
#include "TopDownRPG/TopDownRPG.h"

void UIdleState::Enter()
{
	Super::Enter();

	if(machine->GetOwnerEnemy())
	{
		// TODO : 하드코딩 제거
		auto actor = UGameplayStatics::GetActorOfClass(machine->GetWorld(), ATDRPGPlayer::StaticClass());
		machine->GetOwnerEnemy()->target = Cast<ATDRPGPlayer>(actor);
		
		machine->Transition(EEnemyState::Move);
	}
	else
	{
		PRINT_LOG(TEXT("machine -> owner is null"));
	}
	
}
