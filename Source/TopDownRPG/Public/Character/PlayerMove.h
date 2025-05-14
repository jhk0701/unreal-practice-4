#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerBaseComponent.h"
#include "PlayerMove.generated.h"


UCLASS()
class TOPDOWNRPG_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<class UCharacterMovementComponent> moveComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<USceneComponent> meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 100.0f;	// TODO : 스탯 반영하기

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float ToleranceToDestination = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FVector Destination;

public:
	UPlayerMove();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;

	void InputClick(const FInputActionValue& InputValue);

private:
	void Move(float DeltaTime);
};
