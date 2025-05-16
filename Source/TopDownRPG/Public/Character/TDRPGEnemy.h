#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDRPGEnemy.generated.h"

UCLASS()
class TOPDOWNRPG_API ATDRPGEnemy : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCharacterStatus> statusComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCharacterAbility> abilityComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UCapsuleComponent> collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<USkeletalMeshComponent> skinMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UEnemyFSM> stateMachine;

public:
	ATDRPGEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
