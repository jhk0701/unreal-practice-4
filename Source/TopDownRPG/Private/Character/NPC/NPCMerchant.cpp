// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/NPCMerchant.h"
#include <Components/SphereComponent.h>
#include <Components/CapsuleComponent.h>
#include "CommonConst.h"

#include "TopDownRPG/TopDownRPG.h"

ANPCMerchant::ANPCMerchant()
{
}

void ANPCMerchant::BeginPlay()
{
	Super::BeginPlay();		
	
	// TODO : 취급 데이터 받아오기
}

void ANPCMerchant::Interact()
{
	PRINT_LOG(TEXT("NPC Merchant Interact"));
}
