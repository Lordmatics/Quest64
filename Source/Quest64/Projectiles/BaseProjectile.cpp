// Start 28/12/2018 - Niall Maple & Dane Maple

#include "BaseProjectile.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Utility/Quest64Utils.h"

// Sets default values
ABaseProjectile::ABaseProjectile() :
	m_fProjectileTimer(0.0f),
	m_fProjectileDuration(10.0f),
	m_fSpeed(5.0f),
	m_fSeekAmount(10.0f),
	m_bSeeking(false),
	m_fStopSeekThreshold(50.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateProjectile(DeltaTime);
}

void ABaseProjectile::SetTargetHitPosition(const FVector& vTarget)
{
	m_vSeekTargetPos = vTarget;

	InitialiseProjectile();
}

void ABaseProjectile::InitialiseProjectile()
{
	const FVector vInitPos(GetActorLocation());
	const FVector vTargetPos(m_vSeekTargetPos);
	m_vVelocity = vTargetPos - vInitPos;
	m_vSeekedVelocity = m_vVelocity;
	m_vVelocity = m_vVelocity.GetSafeNormal();
}

float ABaseProjectile::UpdateSeeking(float dt)
{
	const FVector vInitPos(GetActorLocation());
	const FVector vTargetPos(m_vSeekTargetPos);
	FVector targetVel = vTargetPos - vInitPos;
	//targetVel = targetVel.GetSafeNormal();
	Quest64Utils::FSeekHelper<float, float> seekX = Quest64Utils::FSeekHelper<float, float>(m_vSeekedVelocity.X, targetVel.X);
	Quest64Utils::FSeekHelper<float, float> seekY = Quest64Utils::FSeekHelper<float, float>(m_vSeekedVelocity.Y, targetVel.Y);
	Quest64Utils::FSeekHelper<float, float> seekZ = Quest64Utils::FSeekHelper<float, float>(m_vSeekedVelocity.Z, targetVel.Z);
	Quest64Utils::Seek<float, float>(m_fSeekAmount, dt, seekX, seekY, seekZ);
	m_vVelocity = m_vSeekedVelocity = FVector(seekX.m_value, seekY.m_value, seekZ.m_value);
	m_vVelocity = m_vVelocity.GetSafeNormal();
	return targetVel.Size();
}

// https://wiki.unrealengine.com/Draw_3D_Debug_Points,_Lines,_and_Spheres:_Visualize_Your_Algorithm_in_Action
// Debug Draw Examples ^
void ABaseProjectile::UpdateProjectile(float dt)
{
	DrawDebugSphere(GetWorld(), m_vSeekTargetPos, 0.25f, 10, FColor::Red, true);

	// v^2 = u^2 + 2as
	// v = u + at
	// s = ut + 0.5 ( a t^2) / 2
	FVector vPrevLocation = GetActorLocation();// forward / side / above
	m_fProjectileTimer += dt;
	if (m_fProjectileTimer > m_fProjectileDuration)
	{
		Destroy();
		return;
	}

	// Reevaluate velocity every frame
	if (m_bSeeking)
	{
		if (UpdateSeeking(dt) <= m_fStopSeekThreshold && m_fStopSeekThreshold != -1.0f)
		{
			m_bSeeking = false;
		}
	}

	vPrevLocation += m_vVelocity * m_fSpeed;
	SetActorLocation(vPrevLocation, true);
}
