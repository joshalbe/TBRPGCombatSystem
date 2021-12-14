// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	_level = 1;

	_baseHealth = 1;
	_baseMAttack = 1;
	_baseRAttack = 1;
	_baseMDefense = 1;
	_baseRDefense = 1;
	_baseSpeed = 1;
}

APlayerCharacter::APlayerCharacter(int level, int hp, int mAttack, int rAttack, int mDefense, int rDefense, int speed)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_level = level;

	_baseHealth = hp;
	_baseMAttack = mAttack;
	_baseRAttack = rAttack;
	_baseMDefense = mDefense;
	_baseRDefense = rDefense;
	_baseSpeed = speed;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int APlayerCharacter::DealDamage()
{
	return 0;
}

void APlayerCharacter::TakeDamage(int oncomingDamage)
{
	_health -= oncomingDamage;

	if (_health < 0)
		_health = 0;
}

void APlayerCharacter::StatChange(int statStage, int statChanged)
{
	_statStage += statStage;
	if (_statStage < -3)
	{ 
		_statStage = -3;
	}
	else if (_statStage > 3)
	{
		_statStage = 3;
	}

	switch (_statStage)
	{
	case -3: 
		statChanged *= 0.25;
		break;
	case -2:
		statChanged *= 0.5;
		break;
	case -1:
		statChanged *= 0.8;
		break;
	case 0:
		statChanged *= 1;
		break;
	case 1:
		statChanged *= 1.2;
		break;
	case 2:
		statChanged *= 1.5;
		break;
	case 3:
		statChanged *= 2;
		break;
	}
}

void APlayerCharacter::DetermineStats()
{
	_health = (0.05 * (3 * _baseHealth * _level)) + (_level * 2) + 20;
	_maxHealth = _health;
	_mAttack = (0.05 * (3 * _baseMAttack * _level)) + 10;
	_rAttack = (0.05 * (3 * _baseRAttack * _level)) + 10;
	_mDefense = (0.05 * (3 * _baseMDefense * _level)) + 10;
	_rDefense = (0.05 * (3 * _baseRDefense * _level)) + 10;

	_stamina = (0.02 * (_baseSpeed * 2 * _level)) + 10;
}

