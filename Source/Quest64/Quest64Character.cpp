// Start 28/12/2018 - Niall Maple & Dane Maple

#include "Quest64Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AQuest64Character

AQuest64Character::AQuest64Character()
{
	// Set size for collision capsule
	if (UCapsuleComponent* pCapsuleComponent = GetCapsuleComponent())
	{
		pCapsuleComponent->InitCapsuleSize(42.0f, 96.0f);
	}

	// set our turn rates for input
	m_fBaseTurnRate = 45.f;
	m_fBaseLookUpAtRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	if (UCharacterMovementComponent* pCharacterMover = GetCharacterMovement())
	{
		pCharacterMover->bOrientRotationToMovement = true; // Character moves in the direction of input...	
		pCharacterMover->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
		pCharacterMover->JumpZVelocity = 600.f;
		pCharacterMover->AirControl = 0.2f;
	}

	// Create a camera boom (pulls in towards the player if there is a collision)
	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if(m_pSpringArm)
	{
		m_pSpringArm->SetupAttachment(RootComponent);
		m_pSpringArm->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
		m_pSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
		// Create a follow camera
		m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
		if(m_pCamera)
		{
			m_pCamera->SetupAttachment(m_pSpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
			m_pCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AQuest64Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AQuest64Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AQuest64Character::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AQuest64Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AQuest64Character::LookUpAtRate);
}

void AQuest64Character::TurnAtRate(float Rate)
{
	if (const UWorld* pWorld = GetWorld())
	{
		AddControllerYawInput(Rate * m_fBaseTurnRate * pWorld->GetDeltaSeconds());
	}
}

void AQuest64Character::LookUpAtRate(float Rate)
{
	if (const UWorld* pWorld = GetWorld())
	{
		AddControllerPitchInput(Rate * m_fBaseLookUpAtRate * pWorld->GetDeltaSeconds());
	}
}

void AQuest64Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AQuest64Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
