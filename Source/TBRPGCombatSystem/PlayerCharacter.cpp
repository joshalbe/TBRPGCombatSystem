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

void APlayerCharacter::DealDamage(APlayerCharacter target, int movePower, bool isMeleeAttack)
{
	int totalDamage;
	float attackPortion;
	float defensePortion;

	switch (isMeleeAttack)
	{
	case true:
		attackPortion = _battleMAttack + (movePower * (1 + (0.03 * _level)));
		defensePortion = target.GetMDefense() * (1 + (0.03 * target.GetLevel()));
		totalDamage = (attackPortion * attackPortion) / (defensePortion * 3);
		break;
	case false:
		attackPortion = _battleRAttack + (movePower * (1 + (0.03 * _level)));
		defensePortion = target.GetRDefense() * (1 + (0.03 * target.GetLevel()));
		totalDamage = (attackPortion * attackPortion) / (defensePortion * 3);
		break;
	}

	target.TakeDamage(totalDamage);
}

void APlayerCharacter::TakeDamage(int oncomingDamage)
{
	_health -= oncomingDamage;

	if (_health <= 0)
	{
		_health = 0;
		_ableToFight = false;
	}
}

void APlayerCharacter::StatChange(int statStage, int statChanged, int whichStat)
{
	/* Gotta totally rework this
	int _statStage = statChanged;
	_statStage += statStage;


	if (_statStage < -3)
	{ 
		statChanged = -3;
	}
	else if (_statStage > 3)
	{
		statChanged = 3;
	}
	else
	{
		statChanged = _statStage;
	}

	switch (statChanged)
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
	*/
}

void APlayerCharacter::DetermineStats()
{
	_health = (0.05 * (3 * _baseHealth * _level)) + (_level * (1 + (0.01 * _level))) + 20;
	_maxHealth = _health;
	_mAttack = (0.05 * (3 * _baseMAttack * _level)) + 10;
	_rAttack = (0.05 * (3 * _baseRAttack * _level)) + 10;
	_mDefense = (0.05 * (3 * _baseMDefense * _level)) + 10;
	_rDefense = (0.05 * (3 * _baseRDefense * _level)) + 10;

	_stamina = (0.02 * (_baseSpeed * 2 * _level)) + 10;
}

