// Start 28/12/2018 - Niall Maple & Dane Maple

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class QUEST64_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

	virtual void Tick(float DeltaTime) override;

	void SetTargetHitPosition(const FVector& vTarget);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitialiseProjectile(); // Configures velocity on BeginPlay, overridable, call Super to extend
	virtual void UpdateProjectile(float dt); // Updates velocity over time every frame, overridable, call Super to extend

	virtual float UpdateSeeking(float dt); // Returns distance to seek target
protected:

	FVector m_vVelocity;
	FVector m_vSeekedVelocity;
	FVector m_vSeekTargetPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
	float	m_fSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
	float	m_fSeekAmount;

	float	m_fProjectileTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
	float	m_fStopSeekThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
	float	m_fProjectileDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
	bool m_bSeeking;
};
