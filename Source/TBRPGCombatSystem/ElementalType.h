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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void AddWeakness(int addedType);
	virtual void AddResistance(int addedType);

	virtual TArray<int> GetWeaknesses() { return _weak; }
	virtual TArray<int> GetResistances() { return _resist; }

	
		
private:
	int _designationNumber;

	TArray<int> _weak;
	TArray<int> _resist;
	
};
