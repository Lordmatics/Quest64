// Start 28/12/2018 - Niall Maple & Dane Maple

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TemplatePawn.generated.h"

UCLASS()
class QUEST64_API ATemplatePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATemplatePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
