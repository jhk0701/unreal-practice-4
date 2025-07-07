// Fill out your copyright notice in the Description page of Project Settings.


#include "TDRPGEnum.h"

FString FTDRPGEnum::EnumToString(const ERarity InValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERarity"), true);

    if (!EnumPtr)
        return FString("Invalid Enum");

    return EnumPtr->GetDisplayNameTextByIndex((int32)InValue).ToString();
}

FString FTDRPGEnum::EnumToString(const ETableType InValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETableType"), true);
	if (!EnumPtr)
        return FString("Invalid Enum");

	return EnumPtr->GetDisplayNameTextByIndex((int32)InValue).ToString();
}

FString FTDRPGEnum::EnumToString(const EStatus InValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStatus"), true);
    if (!EnumPtr)
        return FString("Invalid Enum");

    return EnumPtr->GetDisplayNameTextByIndex((int32)InValue).ToString();
}

FString FTDRPGEnum::EnumToString(const EAbility InValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAbility"), true);
    if (!EnumPtr)
        return FString("Invalid Enum");

    return EnumPtr->GetDisplayNameTextByIndex((int32)InValue).ToString();
}

FString FTDRPGEnum::EnumToString(const ESkillInputKey InValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESkillInputKey"), true);
    if (!EnumPtr)
        return FString("Invalid Enum");

    return EnumPtr->GetDisplayNameTextByIndex((int32)InValue).ToString();
}
