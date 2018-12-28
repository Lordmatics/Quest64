// Start 28/12/2018 - Niall Maple & Dane Maple

#include "TemplatePawn.h"

// Sets default values
ATemplatePawn::ATemplatePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATemplatePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATemplatePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATemplatePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

