// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
		int mDefense, int rDefense, int speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	int GetLevel() { return _level; }
	int GetMAttack() { return _battleMAttack; }
	int GetRAttack() { return _battleRAttack; }
	int GetMDefense() { return _battleMDefense; }
	int GetRDefense() { return _battleRDefense; }
	int GetSpeed() { return _baseSpeed; }
	int GetStamina() { return _stamina; }

	void AddExp(int expGain) { _exp += expGain; }
	void DealDamage(APlayerCharacter target, int movePower, bool isMeleeAttack);
	void TakeDamage(int oncomingDamage);
	void StatChange(int statStage, int statChanged, int whichStat);

private:
	void DetermineStats();

private:
	bool _ableToFight = true;
	int _level;
	int _exp;

	int _baseHealth;
	int _baseMAttack;
	int _baseRAttack;
	int _baseMDefense;
	int _baseRDefense;
	int _baseSpeed;

	int _maxHealth;
	int _health;
	int _mAttack;
	int _rAttack;
	int _mDefense;
	int _rDefense;
	int _stamina;

	int _battleMAttack;
	int _battleRAttack;
	int _battleMDefense;
	int _battleRDefense;

	int _mAtkStage;
	int _rAtkStage;
	int _mDefStage;
	int _RDefStage;
};
