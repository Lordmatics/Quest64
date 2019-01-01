// Start 28/12/2018 - Niall Maple & Dane Maple

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Quest64Character.generated.h"

UCLASS(config=Game)
class AQuest64Character : public ACharacter
{
	GENERATED_BODY()

	// PRIVATE PROPERTIES
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_pSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* m_pCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = "true"))
	class UStatsComponent* m_pStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseProjectile> m_windProjectileClass;

	// PUBLIC PROPERTIES
public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float m_fBaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float m_fBaseLookUpAtRate;

	// PRIVATE FUNCTIONS
private:

#pragma region Player Control
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
#pragma endregion

#pragma region Player Abilities

	UFUNCTION()
	void FireWindCutter();

#pragma endregion
	// PUBLIC FUNCTIONS
public:
	AQuest64Character();

#pragma region Stats
	UFUNCTION(BlueprintCallable)
		const int GetCurrentHealth() const;
	UFUNCTION(BlueprintCallable)
		const int GetMaxHealth() const;
	UFUNCTION(BlueprintCallable)
		const int GetCurrentMana() const;
	UFUNCTION(BlueprintCallable)
		const int GetMaxMana() const;
	UFUNCTION(BlueprintCallable)
		const int GetDefense() const;
	UFUNCTION(BlueprintCallable)
		const int GetEvasion() const;
#pragma endregion

	// VIRTUALS
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// GETTERS & SETTERS
public:
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return m_pSpringArm; }
	FORCEINLINE class UCameraComponent* GetCamera() const { return m_pCamera; }
	FORCEINLINE class UStatsComponent* GetStats() const { return m_pStats; }
};

