// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonConst.h"

const FName CommonConst::Interaction_ProfileName = FName(TEXT("Interaction"));
const FName CommonConst::PlayerTag = FName(TEXT("Player"));
const FName CommonConst::EnemyTag = FName(TEXT("Enemy"));

// 포맷 형태
const FString CommonConst::PATH_FORMAT_UI = FString(TEXT("/Game/4-UI/WBP_{0}.WBP_{0}_C"));
const FString CommonConst::PATH_FORMAT_DATA_TABLE = FString(TEXT("/Game/5-DataTable/{0}.{0}"));