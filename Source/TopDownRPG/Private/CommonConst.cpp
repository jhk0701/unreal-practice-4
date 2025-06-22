// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonConst.h"

const FName CommonConst::INTERACT_PROFILE = FName(TEXT("Interaction"));
const FName CommonConst::PLAYER_TAG = FName(TEXT("Player"));
const FName CommonConst::ENEMY_TAG = FName(TEXT("Enemy"));

// 포맷 형태
const FString CommonConst::PATH_FORMAT_UI = FString(TEXT("/Game/4-UI/WBP_{0}.WBP_{0}_C"));
const FString CommonConst::PATH_FORMAT_DATA_TABLE = FString(TEXT("/Game/5-DataTable/{0}.{0}"));

const FString CommonConst::DATA_TABLE_CONTEXT = FString(TEXT("Find Row"));

const FName CommonConst::SCENE_LOBBY = FName(TEXT("1-Lobby"));
const FName CommonConst::SCENE_GAME = FName(TEXT("2-Game"));

// 프라이머리 에셋 타입
const FName CommonConst::CONFIG_CHARACTER = FName(TEXT("CharacterConfig"));

const FString CommonConst::GAME_DATA_SLOT = FString(TEXT("GameDataSlot"));