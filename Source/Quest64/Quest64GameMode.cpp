// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Quest64GameMode.h"
#include "Quest64Character.h"
#include "UObject/ConstructorHelpers.h"

AQuest64GameMode::AQuest64GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
