// Fill out your copyright notice in the Description page of Project Settings.


#include "TDRPGConst.h"

const FName FTDRPGConst::INTERACT_PROFILE = FName(TEXT("Interaction"));
const FName FTDRPGConst::PLAYER_TAG = FName(TEXT("Player"));
const FName FTDRPGConst::ENEMY_TAG = FName(TEXT("Enemy"));

// 포맷 형태
const FString FTDRPGConst::PATH_FORMAT_UI = FString(TEXT("/Game/4-UI/WBP_{0}.WBP_{0}_C"));
const FString FTDRPGConst::PATH_FORMAT_DATA_TABLE = FString(TEXT("/Game/5-DataTable/{0}.{0}"));

const FString FTDRPGConst::DATA_TABLE_CONTEXT = FString(TEXT("Find Row"));

const FName FTDRPGConst::SCENE_LOBBY = FName(TEXT("1-Lobby"));
const FName FTDRPGConst::SCENE_GAME = FName(TEXT("2-Game"));

// 프라이머리 에셋 타입
const FName FTDRPGConst::CONFIG_CHARACTER = FName(TEXT("CharacterConfig"));

const FString FTDRPGConst::GAME_DATA_SLOT = FString(TEXT("GameDataSlot"));

const FString FTDRPGConst::EMPTY_ITEM_ID = FString(TEXT("0000"));