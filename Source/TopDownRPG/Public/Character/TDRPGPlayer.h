#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDRPGPlayer.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInputBindDelegate, class UEnhancedInputComponent* , class ATDRPGPlayerController* );

UCLASS()
class TOPDOWNRPG_API ATDRPGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	FOnInputBindDelegate OnInputBindDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FollowingCamera)
	TSubclassOf<class AFollowingCamera> cameraFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FollowingCamera)
	TObjectPtr<AFollowingCamera> cameraInst;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Comp)
	TObjectPtr<class UPlayerMove> moveComp;

public:
	ATDRPGPlayer();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Initialize();

};
