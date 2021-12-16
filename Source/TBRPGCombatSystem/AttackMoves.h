// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackMoves.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBRPGCOMBATSYSTEM_API UAttackMoves : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackMoves();

	UAttackMoves(int movePower, int staminaCost, int moveType, bool isMelee);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	int _movePower;
	int _staminaCost;
	int _moveType;
	bool _isMelee;
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