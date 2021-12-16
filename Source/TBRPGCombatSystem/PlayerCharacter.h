// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttackMoves.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class TBRPGCOMBATSYSTEM_API APlayerCharacter : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

	APlayerCharacter(int level, int hp, int mAttack, int rAttack, 
		int mDefense, int rDefense, int speed, int typeOne, int typeTwo);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Return the base stats for use in operations
	int GetLevel() { return _level; }
	int GetMAttack() { return _battleMAttack; }
	int GetRAttack() { return _battleRAttack; }
	int GetMDefense() { return _battleMDefense; }
	int GetRDefense() { return _battleRDefense; }
	int GetSpeed() { return _baseSpeed; }
	int GetStamina() { return _stamina; }

	void AddExp(int expGain) { _exp += expGain; }
	void DealDamage(APlayerCharacter target, int movePower, bool isMeleeAttack, 
		bool isSTAB, int effectiveness);
	void TakeDamage(int oncomingDamage);
	void StatChange(int statStage, int statChanged, int statChangedInBattle, int amountChanged);
	void ResetStats();

	void CorruptedAffliction();
	void FlashburnAffliction();
	void TerrorAffliction();
	void BurnAffliction();
	void FreezeAffliction();
	void BleedingAffliction();
	void StunAffliction();
	void FracturedAffliction();
	void SleepAffliction();
	void AnnoyedAffliction();

	void UseMove(UAttackMoves attackMove, APlayerCharacter target);

private:
	void LevelUp(int levelsGained);
	void StaminaRecharge(int partyMembersActive);
	void StaminaPenalty();
	void DetermineStats();

	void StatusCheck();

//	The many numbers which make an RPG work while being balanced
private:
	// Basic values of the PlayerCharacter's status
	bool _ableToFight = true;
	int _level;
	int _exp;

	// The base stats of a PlayerCharacter, which never changes
	int _baseHealth;
	int _baseMAttack;
	int _baseRAttack;
	int _baseMDefense;
	int _baseRDefense;
	int _baseSpeed;

	// The maximum amount a PlayerCharacter can have at a given level
	int _maxHealth;
	int _maxStamina;

	// The stats a PlayerCharacter holds at their current level. Only raises permanently through
	// leveling
	int _health;
	int _mAttack;
	int _rAttack;
	int _mDefense;
	int _rDefense;
	int _stamina;

	// The primary combat stats as they are affected in battle through stat raises, lowers, etc.
	// Resets to their previous state after a battle, or after they are switched out
	int _battleMAttack;
	int _battleRAttack;
	int _battleMDefense;
	int _battleRDefense;

	// The amount a stat is being lowered or raised during battle. Resets to 0 after a battle
	int _mAtkStage;
	int _rAtkStage;
	int _mDefStage;
	int _rDefStage;

	// How long a PlayerCharacter is exhausted for.
	int _exhaustionTimer;
	bool _staminaLock;

public:
	int affliction = 0;
	int afflictionTimer;

	int elementalType[2];
};

/*
	Types:
	0. Aqua
	1. Beast
	2. Corruption
	3. Crystal
	4. Earth
	5. Energy
	6. Flame
	7. Frost
	8. Insect
	9. Light
	10. Metal
	11. Nature
	12. Shadow
	13. Spirit
	14. Wind
	-1. No type
*/