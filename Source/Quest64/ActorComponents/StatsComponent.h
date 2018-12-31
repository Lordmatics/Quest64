// Start 28/12/2018 - Niall Maple & Dane Maple

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUEST64_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// GETTERS
	FORCEINLINE const uint32 GetCurrentHealth() const { return m_iCurrentHealth; }
	FORCEINLINE const uint32 GetMaxHealth() const { return m_iMaxHealth; }
	FORCEINLINE const uint32 GetCurrentMana() const { return m_iCurrentMana; }
	FORCEINLINE const uint32 GetMaxMana() const { return m_iMaxMana; }
	FORCEINLINE const uint32 GetDefense() const { return m_iDefense; }
	FORCEINLINE const uint32 GetEvasion() const { return m_iEvasion; }

	// SETTERS
	FORCEINLINE void SetCurrentHealth(const uint32 newHealth) { m_iCurrentHealth = newHealth; }
	FORCEINLINE void SetMaxHealth(const uint32 newMaxHealth) { m_iMaxHealth = newMaxHealth; }
	FORCEINLINE void SetCurrentMana(const uint32 newMana) { m_iCurrentMana = newMana; }
	FORCEINLINE void SetMaxMana(const uint32 newMaxMana) { m_iMaxMana = newMaxMana; }
	FORCEINLINE void SetDefense(const uint32 newDefense) { m_iDefense = newDefense; }
	FORCEINLINE void SetEvasion(const uint32 newEvasion) { m_iEvasion = newEvasion; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

protected:
	uint32 m_iCurrentHealth;
	uint32 m_iMaxHealth;
	uint32 m_iCurrentMana;
	uint32 m_iMaxMana;
	uint32 m_iDefense;
	uint32 m_iEvasion;
};
