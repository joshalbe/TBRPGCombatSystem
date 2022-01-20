// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "AttackMoves.h"
#include "ElementalType.h"
#include "Components/ActorComponent.h"
#include "PlayerHandler.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBRPGCOMBATSYSTEM_API UPlayerHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHandler();

	UPlayerHandler(int level, int hp, int mAttack, int rAttack,
		int mDefense, int rDefense, int speed, UElementalType* typeOne, UElementalType* typeTwo);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Return the base stats for use in operations
	int GetLevel() { return _level; }
	int GetMAttack() { return _battleMAttack; }
	int GetRAttack() { return _battleRAttack; }
	int GetMDefense() { return _battleMDefense; }
	int GetRDefense() { return _battleRDefense; }
	int GetSpeed() { return _baseSpeed; }
	int GetStamina() { return _stamina; }

	//Retrieves the types of the character
	TArray<UElementalType*> GetType() { return typeCombo; }
	UElementalType* GetTypeOne() { return typeCombo[0]; }
	UElementalType* GetTypeTwo() { return typeCombo[1]; }

	//Various necessary tasks to keep the game working as expected
	void AddExp(int expGain) { _exp += expGain; }
	void DealDamage(UPlayerHandler* target, int movePower, char isMeleeAttack,
		bool isSTAB, int effectiveness);
	void TakeDamage(int oncomingDamage);
	void StatChange(int statStage, int statChanged, int statChangedInBattle, int amountChanged);
	void ResetStats();

	//Specific functions for before a move takes effect
	void UseMove(UAttackMoves* attackMove, UPlayerHandler* target);
	int TypeCheck(UAttackMoves* move, UPlayerHandler* target);

	void AddMove(UAttackMoves* move) { knownMoves.Add(move); }
	TArray<UAttackMoves*> GetMoves() { return knownMoves; }

	void AfterBattle();
	
	//Applies an affliction to the PlayerHandler
	void CorruptedAffliction() { affliction = 1; }
	void FlashburnAffliction() { affliction = 2; }
	void TerrorAffliction() { affliction = 3; }
	void BurnAffliction() { affliction = 4; }
	void FreezeAffliction() { affliction = 5; }
	void BleedingAffliction() { affliction = 6; }
	void StunAffliction() { affliction = 7; }
	void FracturedAffliction() { affliction = 8; }
	void SleepAffliction() { affliction = 9; }
	void AnnoyedAffliction() { affliction = 10; }
	

private:
	//Functions the character can handle for itself
	void LevelUp(int levelsGained);
	void StaminaRecharge(int partyMembersActive);
	void StaminaPenalty();
	void DetermineStats();
	void StatusCheck();


private:
	// Basic values of the PlayerHandler's status
	bool _ableToFight = true;
	UPROPERTY(EditAnywhere)
	int _level;
	int _exp;

	// The base stats of a PlayerHandler, which doesn't change through leveling
	UPROPERTY(EditAnywhere)
	int _baseHealth;
	UPROPERTY(EditAnywhere)
	int _baseMAttack;
	UPROPERTY(EditAnywhere)
	int _baseRAttack;
	UPROPERTY(EditAnywhere)
	int _baseMDefense;
	UPROPERTY(EditAnywhere)
	int _baseRDefense;
	UPROPERTY(EditAnywhere)
	int _baseSpeed;

	// The maximum amount a PlayerHandler can have at a given level
	int _maxHealth;
	int _maxStamina;

	// The stats a PlayerHandler holds at their current level. Only raises permanently through
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

	// How long a PlayerHandler is exhausted for.
	int _exhaustionTimer;
	bool _staminaLock;


public:
	//Which affliction the PlayerCharacter has
	int affliction = 0;
	//How much longer the player will be afflicted with the condition
	int afflictionTimer;

	//Array holding the types of the PlayerCharacter
	TArray<UElementalType*> typeCombo;
		
	TArray<UAttackMoves*> knownMoves;

};
