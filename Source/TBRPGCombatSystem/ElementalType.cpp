// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementalType.h"

// Sets default values for this component's properties
UElementalType::UElementalType()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UElementalType::UElementalType(int designationNum) 
{
	_designationNumber = designationNum;
}


// Called when the game starts
void UElementalType::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UElementalType::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UElementalType::AddWeakness(int addedType)
{
	_weak.Add(addedType);
}


void UElementalType::AddResistance(int addedType)
{
	_resist.Add(addedType);
}

