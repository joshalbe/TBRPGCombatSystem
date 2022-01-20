// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementalType.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TBRPGCOMBATSYSTEM_API UElementalType : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElementalType();
	UElementalType(int designationNum);
	UElementalType(TArray<char> typeDesignation);
	UElementalType(int designationNum, TArray<char> typeDesignation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void AddWeakness(UElementalType* addedType);
	virtual void AddResistance(UElementalType* addedType);

	virtual TArray<UElementalType*> GetWeaknesses() { return _weaknesses; }
	virtual TArray<UElementalType*> GetResistances() { return _resistances; }

	virtual int GetDesignationNumber() { return _designationNumber; }
	virtual TArray<char> GetDesignationName() { return _typeDesignation; }
		
private:
	int _designationNumber;
	TArray<char> _typeDesignation;

	TArray<UElementalType*> _weaknesses;
	TArray<UElementalType*> _resistances;
};
