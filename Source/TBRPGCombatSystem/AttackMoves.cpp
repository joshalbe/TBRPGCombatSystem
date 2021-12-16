// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackMoves.h"

// Sets default values for this component's properties
UAttackMoves::UAttackMoves()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_movePower = 0;
	_staminaCost = 0;
	_moveType = -1;
	//_isMelee = null;
}


UAttackMoves::UAttackMoves(int movePower, int staminaCost, int moveType, bool isMelee)
{
	_movePower = movePower;
	_staminaCost = staminaCost;
	_moveType = moveType;
	_isMelee = isMelee;
}


// Called when the game starts
void UAttackMoves::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackMoves::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

