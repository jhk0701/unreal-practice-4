// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Data/ItemDataRow.h"

void UItemBase::Initialize(FItemDataRow* InData, FName* InID)
{
    Data = InData;
    ItemID = InID;

    OnItemUpdated.Broadcast(this);
}

void UItemBase::Initialize(FItemDataRow* InData, FName* InID, uint32 InAmount)
{
    Quantity = InAmount;
    Initialize(InData, InID);
}

/// <summary>
/// 이 아이템 객체에 새로 물량을 더 넣을 수 있는지 확인하고 넣는 메서드
/// </summary>
/// <param name="InAmount">들어올 양</param> 
/// <param name="OutRest">들어오고 남은 양</param>
/// <returns>온전히 모두 받아들였는지 여부</returns>
bool UItemBase::TryAddItem(uint32 InAmount, uint32& OutRest)
{
    if (Data->NumOfDuplicate < Quantity + InAmount)
    {
        // Quantity + InAmount 가 최대 수용치를 넘어섰음 
        Quantity = Data->NumOfDuplicate; // 최대치 수용
        
        // 나머지 계산해서 반환
        OutRest = (Quantity + InAmount) - Data->NumOfDuplicate;

        OnItemUpdated.Broadcast(this);
        return false;
    }

    Quantity += InAmount;
    OnItemUpdated.Broadcast(this);
    return true;
}
