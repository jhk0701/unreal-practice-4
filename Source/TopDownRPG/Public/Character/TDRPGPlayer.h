#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDRPGPlayer.generated.h"

UCLASS()
class TOPDOWNRPG_API ATDRPGPlayer : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> camera;

public:
	ATDRPGPlayer();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
