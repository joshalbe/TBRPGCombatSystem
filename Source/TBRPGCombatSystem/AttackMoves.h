// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "ElementalType.h"
#include "Components/ActorComponent.h"
#include "AttackMoves.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBRPGCOMBATSYSTEM_API UAttackMoves : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UAttackMoves();

	UAttackMoves(int movePower, int staminaCost, UElementalType* moveType, char attackKind);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	int GetPower() { return _movePower; }
	int GetStamCost() {	return _staminaCost; }
	UElementalType* GetMoveType() { return _moveType; }
	char GetAttackKind() { return _attackKind; }


private:
	int _movePower;
	int _staminaCost;
	UElementalType* _moveType;
	char _attackKind;
};
