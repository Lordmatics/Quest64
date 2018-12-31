// Start 28/12/2018 - Niall Maple & Dane Maple

#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Initialise Stats
	SetCurrentHealth(50);
	SetMaxHealth(50);
	SetCurrentMana(15);
	SetMaxMana(15);
	SetDefense(4);
	SetEvasion(5);
	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Load Stats from file
	//SetCurrentHealth(50);
	//SetMaxHealth(50);
	//SetCurrentMana(15);
	//SetMaxMana(15);
	//SetDefense(4);
	//SetEvasion(5);
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

