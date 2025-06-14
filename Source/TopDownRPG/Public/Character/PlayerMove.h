#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerInputComponent.h"
#include "PlayerMove.generated.h"


UCLASS()
class TOPDOWNRPG_API UPlayerMove : public UPlayerInputComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<class UCharacterMovementComponent> MoveComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsWalking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 100.0f;	// TODO : 스탯 반영하기

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float ToleranceToDestination = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float DodgePower = 1000.f;

public:
	UPlayerMove();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;

	void InputClick(const FInputActionValue& InputValue);
	void StopMove();
	void Move(float DeltaTime);

	void InputDodge(const FInputActionValue& InputValue);
	void Dodge();
};
