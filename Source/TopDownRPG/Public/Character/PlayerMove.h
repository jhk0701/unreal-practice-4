#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMove.generated.h"

class ATDRPGPlayer;
class ATDRPGPlayerController;
struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UPlayerMove : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<ATDRPGPlayer> me;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<ATDRPGPlayerController> controller;

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

	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInputComponent, class ATDRPGPlayerController* InController);

	void InputClick(const FInputActionValue& InputValue);

private:
	void Move(float DeltaTime);
};
