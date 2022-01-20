// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHandler.h"
#include "AttackMoves.h"
#include "ElementalType.h"

// Sets default values for this component's properties
UPlayerHandler::UPlayerHandler()
{
	_level = 1;

	_baseHealth = 1;
	_baseMAttack = 1;
	_baseRAttack = 1;
	_baseMDefense = 1;
	_baseRDefense = 1;
	_baseSpeed = 1;


	DetermineStats();
}

/*
	Takes 9 arguments:
	level- the level of the PlayerHandler on first creation
	hp- how much hp the character has
	mAttack- how much melee attack the character has
	rAttack- how much ranged attack the character has
	mDefense- how much melee defense the character has
	rDefense- how much ranged defense the character has
	speed- how much speed the character has
	typeOne- what the first type of the character is
	typeTwo- what the second type of the character is

	Initializes a PlayerHandler, deciding its stats and types based on the inserted arguments
*/
UPlayerHandler::UPlayerHandler(int level, int hp, int mAttack, int rAttack,
	int mDefense, int rDefense, int speed, UElementalType* typeOne, UElementalType* typeTwo)
{
	//Sets the important base stats of the PlayerCharacter
	_level = level;

	_baseHealth = hp;
	_baseMAttack = mAttack;
	_baseRAttack = rAttack;
	_baseMDefense = mDefense;
	_baseRDefense = rDefense;
	_baseSpeed = speed;

	typeCombo.Add(typeOne); typeCombo.Add(typeTwo);

	DetermineStats();
}


// Called when the game starts
void UPlayerHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*
	Takes 5 arguments:
	target- the PlayerCharacter that is being attacked
	movePower- the attack power of the move being used to attack
	isMeleeAttack- whether the attack being used is contact or ranged
	isSTAB- whether the PlayerHandler is the same type as the move
	effectiveness- how much the move affects the target

	The function takes the multiple factors involved with an attack, including the arguments as well
	as stats within the PlayerHandlers to determine how much damage an attack does
*/
void UPlayerHandler::DealDamage(UPlayerHandler* target, int movePower, char isMeleeAttack,
	bool isSTAB, int effectiveness)
{
	// Breaks the many moving parts of the formula down into digestable portions
	int totalDamage;
	float attackPortion;
	float defensePortion;
	float damageModifier;

	//Calculates damage based on whether it's a melee or ranged attack
	switch (isMeleeAttack)
	{
	case 'm':
		attackPortion = _battleMAttack + (movePower * (1 + (0.03 * _level)));
		defensePortion = target->GetMDefense() * (1 + (0.03 * target->GetLevel()));
		totalDamage = (attackPortion * attackPortion) / (defensePortion * 3);
		break;
	case 'r':
		attackPortion = _battleRAttack + (movePower * (1 + (0.03 * _level)));
		defensePortion = target->GetRDefense() * (1 + (0.03 * target->GetLevel()));
		totalDamage = (attackPortion * attackPortion) / (defensePortion * 3);
		break;
	}

	//Takes the effectiveness of the attack, then multiplies the potential STAB by it
	switch (effectiveness)
	{
	case -2:
		if (isSTAB)
		{
			damageModifier = 0.3;
		}
		else
		{
			damageModifier = 0.25;
		}
		break;
	case -1:
		if (isSTAB)
		{
			damageModifier = 0.6;
		}
		else
		{
			damageModifier = 0.5;
		}
		break;
	case 0:
		if (isSTAB)
		{
			damageModifier = 1.2;
		}
		else
		{
			damageModifier = 1.0;
		}
		break;
	case 1:
		if (isSTAB)
		{
			damageModifier = 1.8;
		}
		else
		{
			damageModifier = 1.5;
		}
		break;
	case 2:
		if (isSTAB)
		{
			damageModifier = 2.4;
		}
		else
		{
			damageModifier = 2.0;
		}
		break;
	}

	target->TakeDamage(totalDamage * damageModifier);
}


/*
	Takes 1 argument:
	oncomingDamage- the amount of damage the PlayerCharacter is about to take

	The function will take the damage and apply it to the PlayerCharacter's health, rendering them
	unable to fight if their health reaches 0
*/
void UPlayerHandler::TakeDamage(int oncomingDamage)
{
	_health -= oncomingDamage;

	if (_health <= 0)
	{
		_health = 0;
		_ableToFight = false;
	}
}


/*
	Takes 4 arguments:
	statStage- the amount of change already applied to the stat in question
	statChanged- the specific stat being changed
	statChangedInBattle- the stat being changed, as portrayed within the battle
	amountChanged- how many stages the stat stage will be changed by

	The function will take these arguments, change the stage of the stats, and use that to determine
	what the new stat amount is
*/
void UPlayerHandler::StatChange(int statStage, int statChanged,
	int statChangedInBattle, int amountChanged)
{
	// Change the stat stage by the amount
	statStage += amountChanged;

	// Ensure the stat stage does not exceed 3 or -3
	if (statStage < -3)
	{
		statStage = -3;
	}
	else if (statStage > 3)
	{
		statStage = 3;
	}

	// Change the stat in battle depending on which stage it's at
	switch (statStage)
	{
	case -3:
		statChangedInBattle = statChanged * 0.25;
		break;
	case -2:
		statChangedInBattle = statChanged * 0.5;
		break;
	case -1:
		statChangedInBattle = statChanged * 0.8;
		break;
	case 0:
		statChangedInBattle = statChanged * 1;
		break;
	case 1:
		statChangedInBattle = statChanged * 1.2;
		break;
	case 2:
		statChangedInBattle = statChanged * 1.5;
		break;
	case 3:
		statChangedInBattle = statChanged * 2;
		break;
	}

}


/*
	Takes no arguments.

	Resets all modifiable stats to their previous state.
*/
void UPlayerHandler::ResetStats()
{
	_battleMAttack = _mAttack;
	_battleRAttack = _rAttack;
	_battleMDefense = _mDefense;
	_battleRDefense = _rDefense;
}


/*
	Takes 2 arguments:
	attackMove- the move that the character is using
	target- the character that is being targeted by the move

	Decides whether the attack's move is the same type as the user, then compare's the
	move's type to the target's type. It then puts the determined arguments into the
	damage calculator function
*/
void UPlayerHandler::UseMove(UAttackMoves* attackMove, UPlayerHandler* target)
{
	bool isSTAB = false;

	if (typeCombo[0] == attackMove->GetMoveType() || typeCombo[1] == attackMove->GetMoveType())
	{
		isSTAB = true;
	}

	int effectiveness = TypeCheck(attackMove, target);

	DealDamage(target, attackMove->GetPower(), attackMove->GetAttackKind(), isSTAB, effectiveness);
}


/*
	Takes 2 arguments:
	move- the move a Character is using
	target- the character that's being targeted with the move

	Evaluates the types of the targeted character against the move used against it
*/
int UPlayerHandler::TypeCheck(UAttackMoves* move, UPlayerHandler* target)
{
	int effectiveness = 0;

	//Make sure the types exist
	if (move->GetMoveType() && target->GetTypeOne() && target->GetTypeTwo())
	{
		//Compare the move's type to the first type's list of weaknesses
		for (int i = 0; i < target->GetTypeOne()->GetWeaknesses().Num(); i++)
		{
			if (move->GetMoveType() == target->GetTypeOne()->GetWeaknesses()[i])
			{
				effectiveness += 1;
			}
		}
		//Compare the move's type to the second type's list of weaknesses
		for (int i = 0; i < target->GetTypeTwo()->GetWeaknesses().Num(); i++)
		{
			if (move->GetMoveType() == target->GetTypeTwo()->GetWeaknesses()[i])
			{
				effectiveness += 1;
			}
		}
		//Compare the move's type to the first type's list of resistances
		for (int i = 0; i < target->GetTypeOne()->GetResistances().Num(); i++)
		{
			if (move->GetMoveType() == target->GetTypeOne()->GetResistances()[i])
			{
				effectiveness -= 1;
			}
		}
		//Compare the move's type to the second type's list of resistances
		for (int i = 0; i < target->GetTypeTwo()->GetResistances().Num(); i++)
		{
			if (move->GetMoveType() == target->GetTypeTwo()->GetResistances()[i])
			{
				effectiveness -= 1;
			}
		}

		return effectiveness;
	}

	return 0;
}

void UPlayerHandler::AfterBattle()
{
	ResetStats();
}


/*
	Takes 1 argument:
	levelsGained- how many levels the character has gained

	Levels up the character applied, then redetermines its stats according to its new level
*/
void UPlayerHandler::LevelUp(int levelsGained)
{
	_level += levelsGained;
	DetermineStats();
}


/*
	Takes 1 argument:
	partyMembersActive- the amount of party members that are still able to fight

	The function takes the amount of PlayerCharacters that are still active and uses it to gauge the
	current PlayerCharacter's adrenaline: i.e. the rate at which it recovers stamina between turns
*/
void UPlayerHandler::StaminaRecharge(int partyMembersActive)
{
	int staminaGain;

	switch (partyMembersActive)
	{
	case 0:
		staminaGain = _maxStamina * 0.25;

		if (staminaGain < 5)
			staminaGain = 5;

		break;
	case 1:
		staminaGain = _maxStamina * 0.2;

		if (staminaGain < 4)
			staminaGain = 4;

		break;
	case 2:
		staminaGain = _maxStamina * 0.15;

		if (staminaGain < 3)
			staminaGain = 3;

		break;
	case 3:
		staminaGain = _maxStamina * 0.1;

		if (staminaGain < 2)
			staminaGain = 2;

		break;
	case 4:
		staminaGain = _maxStamina * 0.05;

		if (staminaGain < 1)
			staminaGain = 1;

		break;
	case 5:
		// No stamina will be gained between turns if all party members are able to fight
		staminaGain = 0;
		break;
	}

	_stamina += staminaGain;
	if (_stamina > _maxStamina)
		_stamina = _maxStamina;
}


/*
	Takes no arguments.

	If invoked, the function penalizes the PlayerCharacter for using more stamina than they had
	available by lowering all of its modifiable stats, and preventing it from using moves over its
	stamina limit for 3 turns
*/
void UPlayerHandler::StaminaPenalty()
{
	StatChange(_mAtkStage, _mAttack, _battleMAttack, -2);
	StatChange(_rAtkStage, _rAttack, _battleRAttack, -2);
	StatChange(_mDefStage, _mDefense, _battleMDefense, -2);
	StatChange(_rDefStage, _rDefense, _battleRDefense, -2);

	_exhaustionTimer = 3;
	_staminaLock = true;
}


/*
	Takes no arguments.

	The function works within a specific PlayerCharacter, using its base stats and level
	to determine the actual stats used by the PlayerCharacter
*/
void UPlayerHandler::DetermineStats()
{
	_health = (0.05 * (3 * _baseHealth * _level)) + (_level * (1 + (0.01 * _level))) + 20;
	_maxHealth = _health;
	_mAttack = (0.05 * (3 * _baseMAttack * _level)) + 10;
	_rAttack = (0.05 * (3 * _baseRAttack * _level)) + 10;
	_mDefense = (0.05 * (3 * _baseMDefense * _level)) + 10;
	_rDefense = (0.05 * (3 * _baseRDefense * _level)) + 10;

	_stamina = (0.02 * (_baseSpeed * 2 * _level)) + 10;
	_maxStamina = _stamina;
}


/*
	Takes no arguments.

	Evaluates the timer on status afflictions and exhaustion, and ends the corresponding
	condition if the timer reaches zero.
*/
void UPlayerHandler::StatusCheck()
{
	switch (afflictionTimer)
	{
	case 0:
		affliction = 0;
		break;
	}

	switch (_exhaustionTimer)
	{
	case 0:
		_staminaLock = false;
		break;
	}
}