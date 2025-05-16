#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDRPGEnemy.generated.h"

UCLASS()
class TOPDOWNRPG_API ATDRPGEnemy : public APawn
{
	GENERATED_BODY()

protected:
	TObjectPtr<class UCharacterAbility> AbilityComp;

public:
	ATDRPGEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
