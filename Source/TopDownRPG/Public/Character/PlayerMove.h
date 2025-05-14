#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UPlayerMove : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<class ATDRPGPlayer> me;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<class UCameraComponent> camera;

public:
	UPlayerMove();
	
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

	virtual void SetupInputBinding(UInputComponent* PlayerInputComponent, APlayerController* InController);
		
};
